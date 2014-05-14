#include "Geometry.h"

// Definition of static id
unsigned long int Geometry::mid_inc = 0;

// Constructor
Geometry::Geometry()
{
	mid = mid_inc;
	mid_inc ++;
	mzombie = true;
}
Geometry::~Geometry()
{

}


int Geometry::id()
{
	return mid;
}

bool Geometry::zombie()
{
	return mzombie;
}
