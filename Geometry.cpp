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
	mDim = 3;
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
		std::cerr << "Could not read: "<< fp<< ". Reason: Wrong filetype. Need '.off' or '.obj'." << std::endl;
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
	std::string s(fp);
	std::string off = ".off";
	std::string obj = ".obj";
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
	std::ifstream f;
	f.open(fp);
	if(!f.is_open())
	{
		std::cerr << "Cannot load '"<<fp<<"'. Reason: ifstream.open() failed."<<std::endl;
		return;
	}
	int readFlags;
	int lineNr = 0;
	int vertIndex = 0;
	int faceIndex = 0;

	while( !f.eof() )
	{
		std::string line;
		getline(f, line, '\n');
		
		// Remove comments and trim the line
		size_t pos = line.find_first_of('#');
		if(pos != std::string::npos)
			line.erase(pos);	

		boost::trim(line);

		if(line.length()!=0)
		{
			// If we are reading the header
			if (lineNr == 0)
			{
				readFlags = off_readFirstLine(line);
				if(readFlags == OFF_TYPE_ERR)
				{	
					std::cerr << "Cannot load '" << fp << "'. Reason: Faulty Header"<<std::endl;
					f.close();
					return;
				}
				lineNr++;
				
			// checks if the vertex dimensions are something other than 3
			}else if( ((readFlags & OFF_TYPE_n) == OFF_TYPE_n) && (lineNr == 1) ){
				size_t tok;
				mDim = stoi(line, &tok, 0);
				if(mDim == 0)
				{
					std::cerr << "Cannot load '" << fp << "'. Reason: Ndim cannot be zero."<<std::endl;
					f.close();
					return;
				}
			// If we are reading nrVert, nrFace, nrLine:
			}else if (lineNr == 1){
				size_t tok;
				int i = 0;
				int intVec[3];
				while( (i<3) && (line.length()!=0) )
				{
					intVec[i] = std::stoi(line, &tok, 0);
					line = line.substr(tok);
					i++;
				}
				
				// If there where too few numbers on the second line
				if(i<3)
				{
					std::cerr << "Cannot load '" << fp << "'. Reason: nr of vert/face/lice info Corrupted the File."<<std::endl;
					f.close();
					return;
				}

				mNrVerts = intVec[0];
				mNrFaces = intVec[1];
				mNrLines = intVec[2];
				verts = std::vector< std::vector<float> > (mNrVerts, std::vector<float>(mDim+1,0) );
				faces = std::vector< std::vector<int> > (mNrFaces, std::vector<int>() );
				// Checks if readFlags indicate vertex-normal-data in..off file
				if( ( readFlags & OFF_TYPE_N ) == OFF_TYPE_N )
				{
					normals = std::vector< std::vector<float> >(mNrVerts, std::vector<float>(4,0) );
				}

				// Checks if readFlags indicate vert-color or face-color
				if( (readFlags & OFF_TYPE_C) == OFF_TYPE_C )
				{
					colors = std::vector< std::vector<float> > (mNrVerts, std::vector<float>(4,0) );
				}else{
					colors = std::vector< std::vector<float> > (mNrFaces, std::vector<float>(4,0) );
				}

				lineNr++;

			// IF we are reading vertecies
			}else if ( (lineNr>1) && (lineNr < mNrVerts+2) ){
				
				size_t tok=0;
				int i=0;
				while( (i < mDim)  && (line.length()!=0) )
				{
					verts[vertIndex][i] = std::stod(line, &tok);
					line = line.substr(tok);
					i++;
				}
				
				// If the ammount of data is not what its supposed to be we return 
				if( i < mDim )
				{
					std::cerr << "Cannot load '" << fp << "'. Reason: Vertex-data Corrupted the File."<<std::endl;
					f.close();
					return;
				}
				// If the w-component is specified, we read it.	
				if( ( (readFlags & OFF_TYPE_4) == OFF_TYPE_4) && ( line.length()!=0 ) )
				{
					verts[vertIndex][mDim] = stof(line, &tok);
					i++;
				}else{
					// else they have their w-component defaulted to 1.0
					verts[vertIndex][mDim] = 1.0;
					i++;
				}	
				// Again, if the ammount of data is not what it's supposed to be we return
				if( i<mDim+1 )
				{
					std::cerr << "Cannot load '" << fp << "'. Reason: Vertex-w-component Corrupted the File."<<std::endl;
					f.close();
					return;
				}

				// If we have Normal Data we read it.
				if( (readFlags & OFF_TYPE_N) == OFF_TYPE_N )
				{
					int j=0;
					while( (j<3) && (line.length()!=0) )
					{
						normals[vertIndex][j] = stof(line, &tok);
						line = line.substr(tok);
						j++;
					}
					// Vectors are have their w-component defaulted to 0
					normals[vertIndex][3] = 0.0;
					
					// Again, if the ammount of data is not what it's supposed to be we return
					if( j != 3 )
					{
						std::cerr << "Cannot load '" << fp << "'. Reason: Normal info Corrupted the File."<<std::endl;
						f.close();
						return;						
					}
				}

				// If we have vertex colors we read it.
				if( (readFlags & OFF_TYPE_C) == OFF_TYPE_C )
				{
					mColorType = 1;
					int k=0;
					while( (k<4) && (line.length()!=0))
					{
						colors[vertIndex][k] = stof(line, &tok);
						line = line.substr(tok);
						k++;
					}
					// Again, if the ammount of data is not what it's supposed to be we return
					if( k != 4 )
					{
						std::cerr << "Cannot load '" << fp << "'. Reason: Vertex Color Corruped the File."<<std::endl;
						f.close();
						return;						
					}
				}
				
				// If we have texture coordinates we read it.
				if( (readFlags & OFF_TYPE_N) == OFF_TYPE_ST )
				{
					std::cout << "Texture Coordinates not implemented." << std::endl;
				}
				lineNr++;
				vertIndex++;
			}else if(lineNr < mNrVerts + mNrFaces +2){
				size_t tok;
				int nr = std::stoi(line, &tok, 0);
				line = line.substr(tok);
				
				faces[faceIndex] = std::vector<int>(nr,0);
				
				int i = 0;
				while( (i<nr) && (line.length() != 0) )
				{
					faces[faceIndex][i] = std::stoi(line, &tok, 0);
					line = line.substr(tok);
					i++;
				}
				
				if(i<nr)
				{
					std::cerr << "Cannot load '" << fp << "'. Reason: Face-info Corrupted File."<<std::endl;
					f.close();
					return;	
				}

				if( (readFlags & OFF_TYPE_C) == 0 )
				{
					int j = 0;
					while( (j<4) && (line.length()!=0) )
					{
						colors[faceIndex][j] = std::stof(line, &tok);
						line = line.substr(tok);
						j++;	
					}
					// if some face-color was present we set color-type to 2. 
					if( j != 0 )
					{
						mColorType = 2;
					}
					// If no face color is not or partly present we add a default color of 2/3 instead with opacity of 1
					while(j<4)
					{
						colors[faceIndex][j] = 2.0/3.0;
						
						if(j==3)
						{
							colors[faceIndex][j] = 1.0;
						}
						j++;
					}
				}
				faceIndex++;
				lineNr++;
			}
		}
	}
}

void Geometry::print()
{
	std::cout <<" Geometry "<< mid << std::endl;
	std::cout << boost::format("%d %d %d") % mNrVerts % mNrFaces % mNrLines << std::endl;
	for(int i = 0; i<mNrVerts; i++)
	{
		for (std::vector<float>::iterator it = verts[i].begin() ; it != verts[i].end(); ++it)
    		std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	for(int i = 0; i<mNrFaces; i++)
	{
		for (std::vector<int>::iterator it = faces[i].begin() ; it != faces[i].end(); ++it)
    		std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	int nrOfColors = 0;
	if(mColorType == 1)
	{
		nrOfColors = mNrVerts;
	}else{
		nrOfColors = mNrFaces;
	}
	for(int i = 0; i<nrOfColors; i++)
	{
		for (std::vector<float>::iterator it = colors[i].begin() ; it != colors[i].end(); ++it)
    		std::cout << ' ' << *it;
		std::cout << std::endl;
	}		
	
}

int Geometry::off_readFirstLine(std::string line)
{
	int loadType = OFF_TYPE_NULL;

	size_t subStrLen = 0;
	size_t line_len = line.length();
	// Check that the line ends with OFF
	if(line.compare(line_len-3, 3, "OFF")!=0){
		return OFF_TYPE_ERR;
	}

	line.erase(line_len-3);

	if(line.find("ST",0)!=std::string::npos){
		subStrLen += 2;
		loadType = loadType + OFF_TYPE_ST;
	}

	if(line.find("C",0)!=std::string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_C;
	}

	if(line.find("N",0)!=std::string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_N;
	}

	if(line.find("4",0)!=std::string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_4;
	}

	if(line.find("n",0)!=std::string::npos){
		subStrLen += 1;
		loadType = loadType + OFF_TYPE_n;
	}

	if(subStrLen != line.length()){
		return OFF_TYPE_ERR;
	}else{
		return loadType;
	}
}

void Geometry::readObj(const char fp[])
{
	std::cerr << "OBJ readed not implemented." << std::endl;
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

std::vector< std::vector<float> > Geometry::vertVec()
{
	return verts;
}

int Geometry::nrFaces()
{
	return mNrFaces;
}

std::vector< std::vector<int> > Geometry::faceVec()
{

	return faces;
}

int Geometry::nrLines()
{

	return mNrLines;
}

int Geometry::colorType()
{
	
	return  mColorType;
}				
std::vector< std::vector<float> > Geometry::colorVec()
{

	return colors;
}
