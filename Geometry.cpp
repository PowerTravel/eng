#include "Geometry.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
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
	mNrLines=0;
	mColorType = 0;
	mDim = 0;
}
Geometry::~Geometry()
{

}

// Loads a file
bool Geometry::load(const char fp[])
{
	fileType f = hasEnding(fp);
	if(f==ERR_TYPE)
	{
		cerr << "Could not read: "<< fp<< ". Reason: Wrong filetype. Need '.off' or '.obj'." << endl;
		return false;
	}
	
	if( f == OFF_TYPE)
		readOff(fp);

	if( f == OBJ_TYPE)
		readObj(fp);

	return false;
}

fileType Geometry::hasEnding(const char fp[])
{
	string s(fp);
	string off = ".off";
	string obj = ".obj";
	if(s.length() >= 4)
	{
		if( s.compare(s.length()-4, 4, off)==0 )
			return OFF_TYPE;

		if( s.compare(s.length()-4, 4, obj)==0 )
			return OBJ_TYPE;
	}

	return ERR_TYPE; 
}

void Geometry::readOff(const char fp[])
{
	ifstream f;
	f.open(fp);
	if(!f.is_open())
	{
		cerr << "Cannot load '"<<fp<<"'. Reason: ifstream.open() failed."<<endl;
		return;
	}
	int readFlags;
	int lineNr = 0;

	while( !f.eof() )
	{
		string line;
		getline(f, line, '\n');
		
		// Remove comments and trim the line
		size_t pos = line.find_first_of('#');
		if(pos != string::npos)
			line.erase(pos);	

		boost::trim(line);

		if(line.length()!=0)
		{
			// If we are reading the header
			if (lineNr == 0)
			{
				cout << endl;
				readFlags = off_readFirstLine(line);
				if(readFlags == OFF_TYPE_ERR)
				{	
					cerr << "Cannot load '" << fp << "'. Reason: Faulty Header"<<endl;
					f.close();
					return;
				}
				lineNr++;
			// If we are reading nrVert, nrFace, nrLine:
			}
			if(mDim == 0)
			{
				// checks if the vertex dimnssions are something other than 3
				if( (readFlags & OFF_TYPE_n) == OFF_TYPE_n)
				{
					size_t tok;
					mDim = stoi(line, &tok, 0);
					if(mDim == 0)
					{
						cerr << "Cannot load '" << fp << "'. Reason: Ndim cannot be zero."<<endl;
						f.close();
						return;
					}
				}else{
					mDim = 3;	
				}
			}
			if (lineNr == 1){
				size_t tok;
				mNrVerts = stoi(line, &tok, 0);
				mNrFaces = stoi(line, nullptr, 0);
				mNrLines = stoi(line, nullptr, 0);

				verts = vector< vector<float> >(mNrVerts);
				faces = vector< vector<int> >(mNrFaces);
	
				// Checks if readFlags indicate vertex-normal-data in..off file
				if( ( readFlags & OFF_TYPE_N ) == OFF_TYPE_N )
				{
					normals = vector< vector<float> >(mNrVerts);
				}

				// Checks if readFlags indicate vert-color or face-color
				if( (readFlags & OFF_TYPE_C) == OFF_TYPE_C )
				{
					cout << "Vert Color"<< endl;
					colors = vector< vector<float> >(mNrVerts);
				}else{
					cout << "Face Color" << endl;
					colors = vector< vector<float> >(mNrFaces);
				}

				lineNr++;
				cout << boost::format("%d, %d, %d") % mNrVerts % mNrFaces % mNrLines<<endl;
			}else if ( lineNr < mNrVerts+2 ){
				
				if()

				// Checks if we have 
				if( (readFlags & OFF_TYPE_N) == OFF_TYPE_N )
				{
				
				}

				cout <<"Vert: "<<line<< endl;
				lineNr++;
			}else if(lineNr < mNrVerts + mNrFaces +2){
				cout <<"Face: "<< line<< endl;
				lineNr++;
			}else{

			}
		}
	}
}

int Geometry::off_readFirstLine(string line)
{
	int loadType = OFF_TYPE_NULL;

	size_t subStrLen = 0;
	size_t line_len = line.length();
	// Check that the line ends with OFF
	if(line.compare(line_len-3, 3, "OFF")!=0){
		return OFF_TYPE_ERR;
	}

	line.erase(line_len-3);

	if(line.find("ST",0)!=string::npos){
		subStrLen += 2;
		loadType = loadType + OFF_TYPE_ST;
	}

	if(line.find("C",0)!=string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_C;
	}

	if(line.find("N",0)!=string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_N;
	}

	if(line.find("4",0)!=string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_4;
	}

	if(line.find("n",0)!=string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_n;
	}

	if(subStrLen != line.length()){
		cout <<" LOL"<<endl;
		return OFF_TYPE_ERR;
	}else{
		return loadType;
	}
}

void Geometry::readObj(const char fp[])
{
	cerr << "OBJ readed not implemented." << endl;
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

	return mNrLines;
}

int Geometry::colorType()
{
	
	return  mColorType;
}				
vector< vector<float> > Geometry::colorVec()
{

	return vector< vector<float> >();
}
