#include "Geometry.h"

// Definition of static id
unsigned long int Geometry::mid_inc = 0;

// Constructor
Geometry::Geometry()
{
	mid = mid_inc;
	mid_inc ++;
	mzombie = true;
	mNrVerts = 0;
	mNrFaces = 0;
	mNrLine=0;
	mColorType = 0;
}
Geometry::~Geometry()
{

}

// Loads a file
bool Geometry::load(const char filepath[])
{

	return false;
}

int Geometry::id()
{
	return mid;
}

bool Geometry::zombie()
{
	return mzombie;
}

// Get the list of faces, vertecies, colors and colortype.
int Geometry::nrVerts()
{
	
	return mNrVerts;
}
vector< vector<float> > Geometry::vertVec()
{
	return vector< vector<float> >();
}
int Geometry::nrFaces()
{
	
	return mNrFaces;
}
vector< vector<int> > Geometry::faceVec()
{

	return vector< vector<int> >();
}

int Geometry::nrLines()
{

	return mNrLine;
}

int Geometry::colorType()
{
	
	return  mColorType;
}				
vector< vector<float> > Geometry::colorVec()
{

	return vector< vector<float> >();
}
