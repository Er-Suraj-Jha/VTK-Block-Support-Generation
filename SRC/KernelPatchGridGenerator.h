#pragma once
namespace Support
{
	namespace Kernel
	{
		/*class Point3D
		{
		public:
			Point3D(double inX = 0.0, double inY = 0.0, double inZ = 0.0):mX(inX), mY(inY) , mZ(inZ) {}
			~Point3D() {}
		public:
			double mX;
			double mY;
			double mZ;
		};*/
		// Takes a Polyhydron and grid value as an input and returns 
		// Array of Grid Lines
		class PatchGridGenerator
		{
		public:
			enum class Status
			{
				Success,
				NoPolydata,
				Fail
			};
		public:

			PatchGridGenerator	( );
			~PatchGridGenerator	( );	
	
		private:
			void	createPolygon		(PointsPtr inPoints, PolydataArray& outPolygonPolydataArray);

			void    cut					(double	inCenter[], double	inNormal[], PolydataArray& outGridLines, std::vector<PointsPtr>& point3);

			void	cutInX				(PolydataArray& outGridLines, PolydataArray& outPolygonPolydataArray);
			void	cutInY				(PolydataArray& outGridLines, PolydataArray& outPolygonPolydataArray);

		public:
			void	setMesh				(PolydataPtr		inPolydata);
			
			void	setGridX			(double				inX);
			
			void	setGridY			(double				inY);
			
			void	setGrid				(double				inX, 
										 double				inY );


			Status	generate			(PolydataArray& outPolydataArray, PolydataArray& outPolygonPolydataArray);

			//void	generatePolygons	(PolydataArray& inPolyDataArr, vtkPoints* intersectionPointIn, PolydataArray& outPolygonPolyDataArr);


		private:
			double			mXGrid;
			double			mYGrid;
			PolydataPtr		mPolydata;		    // Input Model
			PlaneCutterPtr	mPlaneCutterPtr;


		};
	}
}