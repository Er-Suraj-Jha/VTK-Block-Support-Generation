#pragma once
#include"Common.h"
#include"KernelPatchGridGenerator.h"

Support::Kernel::PatchGridGenerator::PatchGridGenerator()
{
	mPolydata = nullptr;
	mXGrid = mYGrid = 5.0;
	mPlaneCutterPtr = nullptr;
}

Support::Kernel::PatchGridGenerator::~PatchGridGenerator()
{

}

void	Support::Kernel::PatchGridGenerator::setMesh(PolydataPtr inPolydata)
{
	mPolydata = inPolydata;
}

void	Support::Kernel::PatchGridGenerator::setGridX(double inX)
{
	mXGrid = inX;
}

void	Support::Kernel::PatchGridGenerator::setGridY(double inY)
{
	mYGrid = inY;
}

void	Support::Kernel::PatchGridGenerator::setGrid(double	inX, double inY)
{
	mXGrid = inX;
	mYGrid = inY;
}

void Support::Kernel::PatchGridGenerator::createPolygon(PointsPtr inPoints, PolydataArray& outPolygonPolydataArray)
{
	int numberOfPoints = inPoints->GetNumberOfPoints();
	if (numberOfPoints == 0)
	{
		return;
	}
	vtkNew<vtkPolygon> polygon;
	int updated_size = numberOfPoints + 2;

	polygon->GetPointIds()->SetNumberOfIds(updated_size);
	for (int k = 0; k < updated_size; k++)
	{
		polygon->GetPointIds()->SetId(k, k);

	}

	//Add the polygon to list of polygons
	vtkNew<vtkCellArray> polygons;
	polygons->InsertNextCell(polygon);

	//Find the start and end point 
	double p[3], q[3];
	inPoints->GetPoint(0, p);
	inPoints->GetPoint(numberOfPoints - 1, q);

	//Create a Polydata to store polygons 
	vtkNew<vtkPolyData> polygonPolyData;
	vtkNew<vtkPoints> point3;
	point3->InsertNextPoint(p[0], p[1], 0.0);
	point3->InsertNextPoint(q[0], q[1], 0.0);
	for (int j = numberOfPoints - 1; j >= 0; j--)
	{
		double point[3];
		inPoints->GetPoint(j, point);
		point3->InsertNextPoint(point[0], point[1], point[2]);
	}

	polygonPolyData->SetPoints(point3);
	polygonPolyData->SetPolys(polygons);
	outPolygonPolydataArray.push_back(polygonPolyData);
}

void   Support::Kernel::PatchGridGenerator::cut(double	inCenter[], double	inNormal[], PolydataArray& outGridLines, std::vector<PointsPtr>& point3)
{
	bool isXplane = (inNormal[0] != 0.0) ? true : false;

	PolydataPtr newPolyData = PolydataPtr::New();
	auto desiredNormalsArray = vtkSmartPointer<vtkCellArray>::New();

	if (mPlaneCutterPtr == nullptr)
	{
		//mPlaneCutterPtr = PlaneCutterPtr::New();
		//mPlaneCutterPtr->SetInputData(mPolydata);
		//mPlaneCutterPtr->SetBuildTree(true);
	}



	vtkNew<vtkPlane> cutPlane;
	cutPlane->SetOrigin(inCenter);
	cutPlane->SetNormal(inNormal);

	//mPlaneCutterPtr->SetPlane(cutPlane);
	//mPlaneCutterPtr->Update();
	//outGridLines.push_back(mPlaneCutterPtr->GetOutput());

	vtkNew<vtkCutter> cutter;
	cutter->SetCutFunction(cutPlane);
	cutter->SetInputData(mPolydata);
	cutter->Update();

	//auto sortX = [](Point3D& inP1, Point3D& inP2)
	//{
	//	if (true)
	//		return inP1.mY < inP2.mY;
	//	else
	//		return inP1.mX < inP2.mX;

	//};
	//std::map<double,Point3D> mapPoint3D;
	//if (cutter->GetOutput()->GetNumberOfPoints() == 0)
	//{
	//	return;
	//}
	//for (int i = 0; i < cutter->GetOutput()->GetNumberOfPoints(); i++)
	//{
	//	if(isXplane)
	//		mapPoint3D.insert({ cutter->GetOutput()->GetPoint(i)[1],{cutter->GetOutput()->GetPoint(i)[0],cutter->GetOutput()->GetPoint(i)[1],cutter->GetOutput()->GetPoint(i)[2] } });
	//	else
	//		mapPoint3D.insert({ cutter->GetOutput()->GetPoint(i)[0],{cutter->GetOutput()->GetPoint(i)[0],cutter->GetOutput()->GetPoint(i)[1],cutter->GetOutput()->GetPoint(i)[2] } });
	//}
	//point3->InsertNextPoint(mapPoint3D.begin()->second.mX, mapPoint3D.begin()->second.mY, mapPoint3D.begin()->second.mZ);
	//point3->InsertNextPoint(mapPoint3D.rbegin()->second.mX, mapPoint3D.rbegin()->second.mY, mapPoint3D.rbegin()->second.mZ);

	

	vtkNew<vtkStripper> stripper;
	stripper->SetInputConnection(cutter->GetOutputPort());
	stripper->JoinContiguousSegmentsOn();
	stripper->Update();


	auto var = stripper->GetOutput()->GetNumberOfCells();
	//std::cout << "Number of Cells " << var << endl;
	if (var > 0)
	{
		for (int i = 0; i < var; i++)
		{

			auto points = stripper->GetOutput()->GetCell(i)->GetPoints();
			int n = points->GetNumberOfPoints();
			vtkNew<vtkPoints> LinePointsTemp;

			if (n > 1)
			{
				for (int j = 0; j < n; j++)
				{
					double p[3];
					points->GetPoint(j, p);
					LinePointsTemp->InsertNextPoint(p[0], p[1], p[2]);
				}
			}
			point3.push_back(LinePointsTemp);

		}
	}

	outGridLines.push_back(cutter->GetOutput());




	//TODO: Add Debug Macro
#ifdef DEBUG_PatchGridGenerator
	std::cout << "\n Grid has points: " << cutter->GetOutput()->GetNumberOfPoints() << std::endl;
#endif
	return;
}

void Support::Kernel::PatchGridGenerator::cutInY(PolydataArray& outGridLines, PolydataArray& outPolygonPolydataArray)
{
	double minY = mPolydata->GetBounds()[2];
	double maxY = mPolydata->GetBounds()[3];

	double startPoint[] = { mPolydata->GetBounds()[0],mPolydata->GetBounds()[2],mPolydata->GetBounds()[4] };
	double normal[] = { 0, 1, 0 };
	for (double y = minY; y <= maxY; y += mYGrid)
	{
		std::vector<PointsPtr> sortedPoints;
		double center[] = { startPoint[0], y, startPoint[2] };
		cut(center, normal, outGridLines, sortedPoints);
		
		for (int j = 0; j < sortedPoints.size(); j++)
		{
				createPolygon(sortedPoints[j], outPolygonPolydataArray);
		}
	
	}
    return;
}



void Support::Kernel::PatchGridGenerator::cutInX(PolydataArray& outGridLines, PolydataArray& outPolygonPolydataArray)
{

	double minX = mPolydata->GetBounds()[0];
	double maxX = mPolydata->GetBounds()[1];

	double startPoint	[] = { mPolydata->GetBounds()[0],mPolydata->GetBounds()[2],mPolydata->GetBounds()[4] };
	double normal		[] = { 1, 0, 0 };

	for (double x = minX; x <= maxX; x += mXGrid)
	{
		std::vector<PointsPtr>sortedPoints;
		double center[] = { x, startPoint[1], startPoint[2] };
		cut(center, normal, outGridLines, sortedPoints);
		for (int j = 0; j < sortedPoints.size(); j++)
		{
			createPolygon(sortedPoints[j], outPolygonPolydataArray);
		}
	}
    return;
}

Support::Kernel::PatchGridGenerator::Status	Support::Kernel::PatchGridGenerator::generate(PolydataArray& outPolydataArray, PolydataArray& outPolygonPolydataArray)
{
	if (mPolydata == nullptr)
		return Support::Kernel::PatchGridGenerator::Status::NoPolydata;

	cutInX(outPolydataArray, outPolygonPolydataArray);
	cutInY(outPolydataArray, outPolygonPolydataArray);

	return Support::Kernel::PatchGridGenerator::Status::Success;
}

//void Support::Kernel::PatchGridGenerator::generatePolygons(PolydataArray& inPolyDataArr, vtkPoints* intersectionPointIn, PolydataArray& outPolygonPolyDataArr)
//{
//	int size = intersectionPointIn->GetNumberOfPoints();
//
//
//	//Polygons with base support
//	static int index = 0;
//
//	for (int i = 0; i < inPolyDataArr.size(); i++)
//	{
//		if (i == 0 || i == (inPolyDataArr.size() / 2 - 1))
//			continue;
//		double p[3], q[3];
//		intersectionPointIn->GetPoint(index, p);
//		intersectionPointIn->GetPoint(index + 1, q);
//
//		index += 2;
//
//		vtkNew<vtkPolygon> polygon;
//		//vtkNew<vtkPolyLine> polyLine;
//		int ind_line_size = inPolyDataArr[i]->GetNumberOfPoints();
//		int updated_size = ind_line_size + 2;
//
//
//		polygon->GetPointIds()->SetNumberOfIds(updated_size); // make a polygon
//		//polyLine->GetPointIds()->SetNumberOfIds(updated_size); // make a polygon
//
//		for (int i = 0; i < updated_size; i++)
//		{
//			polygon->GetPointIds()->SetId(i, i);
//			//polyLine->GetPointIds()->SetId(i, i);
//
//		}
//
//		vtkNew<vtkCellArray> polygons;
//		polygons->InsertNextCell(polygon);
//		//polygons->InsertNextCell(polyLine);
//
//
//		vtkNew<vtkPolyData> polygonPolyData;
//
//		vtkNew<vtkPoints> point3;
//		point3->InsertNextPoint(p[0], p[1], 0.0);
//		point3->InsertNextPoint(q[0], q[1], 0.0);
//
//		for (int k = ind_line_size - 1; k >= 0; k--)
//		{
//			double r[3];
//			inPolyDataArr[i]->GetPoint(k, r);
//			point3->InsertNextPoint(r[0], r[1], r[2]);
//
//		}
//
//
//		polygonPolyData->SetPoints(point3);
//
//		polygonPolyData->SetPolys(polygons);
//
//		outPolygonPolyDataArr.push_back(polygonPolyData);
//		
//	}
//}



