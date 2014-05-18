#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
// Geometry class, Holds geometry data
// Can load off files and at some later
// pointa also other types of files
using namespace std;
class Geometry
{
	public:

		Geometry();
		virtual ~Geometry();

		bool load(const char filepath[]);

		// Getters:
		int id();		// The objects ID
		bool zombie();	// The objects zombie-status

		// Get the list of faces, vertecies, colors and colortype.
		int nrVerts();
		vector< vector<float> >vertVec();
		int nrFaces();
		vector< vector<int> > faceVec();
		int nrLines();
		int colorType();				// 0=no Color, 1=vert, 2=face
		vector< vector<float> >colorVec();

		 
	private:

		// Data members have a m before their name to differentiate them from functions.

		// Id for objects
		static unsigned long int mid_inc;
		unsigned long int mid;
		
		// Flag if the object is working properly
		bool mzombie;
		
		int mNrVerts;
		int mNrFaces;
		int mNrLine;
		int	mColorType;
};

#endif // GEOMETRY_h
