#include "Common.h"
#include "KernelOverHangDetector.h"

using namespace Support::Kernel;
//#define DEBUG_CODE_OverhangDetector
void	OverhangDetector::setMesh(PolydataPtr inPolydata)
{
	mPolydata = inPolydata;
}
void	OverhangDetector::cleanMesh(PolydataPtr inPolyData)
{
#ifdef DEBUG_CODE_OverhangDetector
	std::cout << "\n Before Cleaning Data: " << inPolyData->GetNumberOfPoints() << " vertices" << std::endl;
	std::cout << "\n Before Cleaning Data:" << inPolyData->GetNumberOfPolys() << " Polys." << std::endl;
#endif

	auto cleanPolyData = vtkSmartPointer<vtkCleanPolyData>::New();
	cleanPolyData->SetInputData(inPolyData);
	cleanPolyData->Update();

#ifdef DEBUG_CODE_OverhangDetector
	std::cout << "\n After Cleaning Data: " << inPolyData->GetNumberOfPoints() << " vertices" << std::endl;
	std::cout << "\n After Cleaning Data:" << inPolyData->GetNumberOfPolys() << " Polys." << std::endl;
#endif

	return;
}

void	OverhangDetector::setCriticalAngle(const double	inCriticalAngle)
{
	mCriticalAngle = inCriticalAngle;
	return;
}

void	OverhangDetector::generateNormals()
{
	auto nrmlGenerator = PolydataNormals::New();
	nrmlGenerator->SetInputData(mPolydata);
	nrmlGenerator->ConsistencyOn();
	nrmlGenerator->AutoOrientNormalsOn();	//Normal Corrction
	nrmlGenerator->ComputePointNormalsOff();
	nrmlGenerator->ComputeCellNormalsOn();
	nrmlGenerator->Update();

	mPolydata = nrmlGenerator->GetOutput();
	return;
}
bool	OverhangDetector::hasNormals()
{
	// TODO: to put the check of the Normals
	return false;
}


OverhangDetector::Status		OverhangDetector::detect(PolydataPtr outPolydata)
{
	if (!mPolydata)
		return OverhangDetector::Status::NoPolydata;

	if (!hasNormals())
		generateNormals();

#ifdef DEBUG_CODE_OverhangDetector
	std::cout << "\n There are: " << mPolydata->GetNumberOfCells() << " cells." << std::endl;
	std::cout << "\n There are: " << mPolydata->GetNumberOfPoints() << " Points." << std::endl;
#endif
	
	vtkSmartPointer<vtkFloatArray> nrmlDataArr =	vtkFloatArray::SafeDownCast(mPolydata->GetCellData()->GetArray("Normals"));

	if (!nrmlDataArr)	return Status::UnableToGnerateNormal;
	
	auto value				= -cos(mCriticalAngle * SUPP_PI / 180.0);
	auto overhangCellArray	= vtkSmartPointer<vtkCellArray>::New();

	for (int i = 0; i < nrmlDataArr->GetSize() / 3; i++)
	{
		auto index = i * 3;
        if (nrmlDataArr->GetValue(index + 2) < value)
			overhangCellArray->InsertNextCell(mPolydata->GetCell(i));

	}

	outPolydata->SetPoints(mPolydata->GetPoints());
	outPolydata->SetPolys(overhangCellArray);

	//Remove the unwanted points
	cleanMesh(outPolydata);
    
#ifdef DEBUG_CODE_OverhangDetector
	std::cout << "\n Out Polyhydon -  There are: " << outPolydata->GetNumberOfCells() << " cells." << std::endl;
	std::cout << "\n Out Polyhydon -  There are: " << outPolydata->GetNumberOfPoints() << " Points." << std::endl;
#endif

	return OverhangDetector::Status::Success;
}

