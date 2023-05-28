#include <iostream>
#include "Common.h"
#include "KernelOverHangDetector.h"
#include "KernelPatchGridGenerator.h"

static vtkSmartPointer<vtkActor>    _createActor(PolydataPtr inPolydata, double  color[], bool inTransprancy = false)
{
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(inPolydata);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(color);
	actor->GetProperty()->SetLineWidth(10);
	actor->GetProperty()->SetPointSize(20);

	if (inTransprancy)	actor->GetProperty()->SetOpacity(0.5);
	return actor;
}
//static vtkSmartPointer<vtkActor>    buildPlate(double inLegth, double inWidth, double )
//{
//	vtkSmartPointer<vtkPolyDataMapper> mapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//	mapper->SetInputData(inPolydata);
//
//	vtkSmartPointer<vtkActor> actor =
//		vtkSmartPointer<vtkActor>::New();
//	actor->SetMapper(mapper);
//	actor->GetProperty()->SetColor(color);
//	actor->GetProperty()->SetPointSize(2);
//
//	if (inTransprancy)	actor->GetProperty()->SetOpacity(0.5);
//	return actor;
//}

int main()
{
	double _red[] = { 1,0,0 };
	double red[] = { .8,.8,0.5 };
	double blue[] = { 0.0,.0,1.0 };
	double green[] = { 0.0,1.0,.0 };
	double yellow[] = { .7,.7,.7 };

	auto renderer = vtkSmartPointer<vtkRenderer>::New();

	// STL Load
	auto reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName("C:\\Users\\SURAJ JHA\\Desktop\\Programmig\\STL_Files\\Sphere_25.stl");
	reader->Update();
	

	std::cout << "\n Support Generation Started";
	using StatusOvh = Support::Kernel::OverhangDetector::Status;
	
	auto overHangPoly = PolydataPtr::New();
	Support::Kernel::OverhangDetector ovh;
	ovh.setMesh(reader->GetOutput());
	ovh.setCriticalAngle(65.0);
	if (ovh.detect(overHangPoly) != StatusOvh::Success)
		return -1;

	//Suraj Added
	PolydataArray polydataArray;
	PolydataArray polydataArray2;

	//vtkNew<vtkPoints> points;
	Support::Kernel::PatchGridGenerator pg;
	pg.setMesh(overHangPoly);
	pg.setGrid(1,1);
	pg.generate(polydataArray, polydataArray2);
	//pg.generatePolygons(polydataArray, points.GetPointer(),polydataArray2);
	
	//Intersection Points ended


	/*int size = points->GetNumberOfPoints();
	vtkNew<vtkPolyLine> polyLine;
	polyLine->GetPointIds()->SetNumberOfIds(size);
	for (unsigned int i = 0; i < size; i++)
	{
		polyLine->GetPointIds()->SetId(i, i);
	}

	vtkNew<vtkCellArray> cells;
	cells->InsertNextCell(polyLine);
	vtkNew<vtkPolyData> polyData;
	polyData->SetPoints(points);
	polyData->SetLines(cells);*/


	std::cout << "\n Support Generation Completed";

	//for (auto it : polydataArray)
	//{
	//	renderer->AddActor(_createActor(it, blue, false));
	//}

	
	for (auto it2 : polydataArray2)
	{
		renderer->AddActor(_createActor(it2, green, false));
	} 
	//renderer->AddActor(_createActor(reader->GetOutput(), red, false));

	//renderer->AddActor(_createActor(overHangPoly, _red, false));

	//renderer->AddActor(_createActor(polygonPolyData, green, false));
	//renderer->AddActor(_createActor(polyData, green, false));



	auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(600, 600);

	auto tarckballStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetInteractorStyle(tarckballStyle);
	interactor->SetRenderWindow(renderWindow);
	renderer->SetBackground(0.3, 0.5, 0.7);
	renderWindow->Render();

	interactor->Start();

}