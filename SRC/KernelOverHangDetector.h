#pragma once
namespace Support
{
	namespace Kernel
	{

		// Takes a Polyhydron as an input and returns the 
		//overhange triangles as Polyhydron
		class OverhangDetector 
		{

		public:
			enum class Status
			{
				Success,
				NoPolydata,
				UnableToGnerateNormal,
				Unknown
			};

		public:

			OverhangDetector			( ){}
			~OverhangDetector			( ){}

		protected:
			bool		hasNormals			( );
			void		generateNormals		( );
			void		cleanMesh			(PolydataPtr		inPolyData );

		public:
			void	setMesh					(PolydataPtr		inPolydata );
			void	setCriticalAngle		(const double		inCriticalAngle );
			Status	detect					(PolydataPtr		outPolydata);

		private:
            double			mCriticalAngle;	    // In Degree
			PolydataPtr		mPolydata;		    // Input Model
		};

	}
}