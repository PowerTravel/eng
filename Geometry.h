#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <vector>

enum fileType{
	ERR_TYPE,	// unrecognized
	OFF_TYPE,	// .off type
	OBJ_TYPE	// .obj type
};

enum offType{
	OFF_TYPE_ERR = -1,
	OFF_TYPE_NULL = 0,
	OFF_TYPE_ST = 1,
	OFF_TYPE_C = 2,
	OFF_TYPE_N = 4,
	OFF_TYPE_4 = 8,
	OFF_TYPE_n = 16
};
inline offType operator|(offType a, offType b)
{return static_cast<offType>(static_cast<int>(a) | static_cast<int>(b));}

// Geometry class, Holds geometry data
// Can load off files and at some later
// pointa also other types of files

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
		std::vector< std::vector<float> >vertVec();
		int nrFaces();
		std::vector< std::vector<int> > faceVec();
		int nrLines();
		int colorType();				// 0=no Color, 1=vert, 2=face
		std::vector< std::vector<float> >colorVec();
		void print();
		 
	private:

		// Data members have a m before their name to differentiate them from functions.

		// Id for objects
		static unsigned long int mid_inc;
		unsigned long int mid;
		
		// Flag if the object is working properly
		bool mzombie;
		
		int mNrVerts;
		int mNrFaces;
		int mNrLines;
		int	mColorType;
		int mDim;

		std::vector< std::vector<float> > verts;
		std::vector< std::vector<int> > faces;
		std::vector< std::vector<float> > colors;
		std::vector< std::vector<float> > normals;

		fileType hasEnding(const char fp[]);
		void readOff(const char fp[]);
		int off_readFirstLine(std::string line);
		void readObj(const char fp[]);
};

#endif // GEOMETRY_h
