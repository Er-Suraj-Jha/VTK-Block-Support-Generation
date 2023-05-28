#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <numeric>
#include <map>
#include <vector>

typedef unsigned long long pop_t;
#define vtkRenderingCore_AUTOINIT 4(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingFreeType,vtkRenderingOpenGL2)
#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

constexpr double feetToMeter(double n)
{
    return n * 0.3048;
}


//#include "Point3D.h"
//#include "Wall.h"
//#include "UtilityDispaly.h"
//
//typedef std::vector<Point3D> ArrPoints;
//typedef std::vector<WallGroup> ArrWllGroup;

#include <vtkVoxelContoursToSurfaceFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataReader.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>
#include <vtkCellData.h>
#include <vtkCellArray.h>
#include <vtkCell.h>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkExtractEdges.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkFeatureEdges.h>
#include <vtkLine.h>
#include <vtkPolygon.h>
#include <vtkDecimatePro.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkAppendPolyData.h>
#include <vtkStripper.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkLineSource.h>
#include <vtkRegularPolygonSource.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkVectorText.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkCylinderSource.h>
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkMath.h>
#include <vtkConeSource.h>
#include <vtkCellLocator.h>
#include <vtkSTLWriter.h>
#include <vtkOBBTree.h>
#include <vtkPlane.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
// #include <vtkInteractorStyle.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkWindowToImageFilter.h>
#include <vtkContourTriangulator.h>
#include <vtkFillHolesFilter.h>
#include <vtkQuadricDecimation.h>
#include <vtkTriangle.h>
#include <vtkCurvatures.h>
#include <vtkPointData.h>
#include <vtkDelaunay2D.h>
#include <vtkTriangleStrip.h>
#include <vtkClipPolyData.h>
#include <vtkDijkstraGraphGeodesicPath.h>
#include <vtkClipClosedSurface.h>
#include <vtkPlaneCollection.h>
#include <vtkPlaneSource.h>
#include <vtkSuperquadricSource.h>
#include <vtkDataSetWriter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkIdFilter.h>
#include <vtkBox.h>
#include <vtkContourWidget.h>
#include <vtkOrientedGlyphContourRepresentation.h>
#include <vtkTubeFilter.h>
#include <vtkDiskSource.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkImplicitPolyDataDistance.h>
#include <vtkDelaunay3D.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTransform.h>
#include <vtkAxesActor.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkIntersectionPolyDataFilter.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkThreshold.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>
#include <vtkHull.h>
#include <vtkPolygonalSurfaceContourLineInterpolator.h>
#include <vtkBSplineTransform.h>
#include <vtkPolyDataWriter.h>
#include <vtkPropPicker.h>
#include <vtkPointLocator.h>
#include <vtkKdTreePointLocator.h>
#include <vtkType.h>
#include <vtkGeometryFilter.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyLine.h>
#include <vtkGenericCell.h>
#include <vtkSelectPolyData.h>
#include <vtkImplicitBoolean.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkGraphToPolyData.h>
#include <vtkDistancePolyDataFilter.h>
#include <vtkImplicitSelectionLoop.h>
#include <vtkMarchingCubes.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkReverseSense.h>
#include <vtkRuledSurfaceFilter.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkInteractorStyleSwitch.h>
#include <vtkPolyDataSilhouette.h>
#include <vtkConvexHull2D.h>
#include <vtkSmartPointer.h>
// To setup the ContourWidget and its representation:
#include <vtkContourWidget.h>
#include <vtkProperty.h>
#include <vtkOrientedGlyphContourRepresentation.h>
// To create the geometry:
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkMath.h>
// Usual VTK pipeline elements:
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkPointPicker.h>
#include <vtkRendererCollection.h>
#include <vtkCallbackCommand.h>
#include <vtkThresholdPoints.h>
#include <vtkConnectivityFilter.h>
#include <vtkVector.h>
#include <vtkExtractPolyDataGeometry.h>
#include <vtkBoundingBox.h>
#include <vtkImplicitDataSet.h>
#include <vtkAppendPolyData.h>
#include <vtkSortDataArray.h>
#include <vtkPCANormalEstimation.h>
#include <vtkSplineFilter.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCenterOfMass.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSliderWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkCommand.h>
#include <vtkWidgetEvent.h>
#include <vtkCallbackCommand.h>
#include <vtkWidgetEventTranslator.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkProperty.h>
#include <vtkLoopSubdivisionFilter.h>
#include <vtkArrowSource.h>
#include <vtkTextSource.h>
#include <vtkQuaternion.h>
#include <vtkSelection.h>
#include <vtkSelectionNode.h>
#include <vtkExtractSelection.h>
#include <vtkRenderLargeImage.h>
#include <vtkJPEGWriter.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkCellPicker.h>
#include <vtkStructuredGrid.h>
#include <vtkCellCenters.h>
#include <vtkPlaneCutter.h>
//#include <vtkPolyDataPlaneCutter.h>


#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define SUPP_PI 3.141592653589793238
typedef vtkSmartPointer<vtkPolyData>        PolydataPtr;
typedef vtkSmartPointer<vtkPlane>           VtkPlanePtr;
typedef vtkSmartPointer<vtkPlane>           PlanePtr;
typedef vtkSmartPointer<vtkPoints>          PointsPtr;
typedef vtkSmartPointer<vtkPlaneCutter>     PlaneCutterPtr;

typedef vtkPolyDataNormals                  PolydataNormals;
typedef std::vector<PolydataPtr>            PolydataArray;
typedef std::vector<double>                 doubleArray;
typedef std::vector<int>                    IntArray;
typedef std::vector<doubleArray>            ColorArray;
typedef vtkSmartPointer<vtkActor>			ActorPtr;
typedef std::vector<ActorPtr>				ActorArr;

//typedef vtkSmartPointer<vtkPolyDataPlaneCutter>     PolyDataPlaneCutter;
