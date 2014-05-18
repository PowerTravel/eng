#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Geometry.h"

// Test Struct:
struct gtGeom{
	int nrVert, nrFace, nrLine;
	float** vl;
	int** fl;
	float** cl;
};

// Global name for testfile
const char TESTFILE[] = "pyramidTest.off";

using namespace std;

bool remove_test_file(const char* filename)
{
	if( remove(filename) != 0 )
	{
		cerr << "remove" << TESTFILE << "failed" << endl;
		return false;	
	}else{
		return true;
	}
}

/* 	Test 1:
 *	Tests constructor and destructors.
 *  Creates and deletes ten geometries and makes sure that their id is correct.
 *	Aditional operations may be created as they become needed.
 */
int test_construct_destruct()
{	
	cout << "\tTesting constructor and destructor... ";
	for(int i=0; i<10; i++)	{
		Geometry geom = Geometry();
		if( geom.id() != i){
			cout << "failed."<<endl;
			return 1;
		}
	}

	cout << "done." << endl;
	return 0;
}


bool test_vert_loop(Geometry* geom, int len ,float** gt)
{
	vector< vector<float> > arr = geom->vertVec();
	if(arr.size() != (unsigned int) len)
		return false;

	for(int i=0; i<len; i++) {
		if (arr[i].size() != 4)
			return false;
		
		for (int j=0; j<4; j++) {
			if ( arr[i][j] != gt[i][j]) {
				return false;
			}
		}
	} 	
	return true;
}

bool test_face_loop(Geometry* geom, int len , int** gt)
{
	vector< vector<int> > arr = geom->faceVec();
	if(arr.size() != (unsigned int) len)
		return false;

	for(int i=0; i<len; i++) {
		if (arr[i].size() != 4)
			return false;
		
		int lineLen = gt[i][0];
		for (int j=1; j<lineLen; j++) {
			if ( arr[i][j] != gt[i][j]) {
				return false;
			}
		}
	} 	
	return true;
}

bool test_color_loop(Geometry* geom, int len ,float** gt)
{
	vector< vector<float> > arr = geom->colorVec();
	if(arr.size() != (unsigned int)len)
		return false;

	for(int i=0; i<len; i++) {
		if (arr[i].size() != 4)
			return false;

		for (int j=0; j<4; j++) {
			if ( arr[i][j] != gt[i][j])
				return false;
			
		}
	} 
	return true;
}
int	test_load_OFF_NoColor()
{	
	cout << "\tTrying to load a .off file without color info... ";
	int failState = 0;
	
	//* Create Ground Truth *//
	int nrVert = 4, nrFace = 4, nrLine = 6, colorType = 0;	
	// Ground Truth Vertex Array
	float vArr[4][4] = { {  0.5, -0.5, -0.5, 1.0},
						   {  0.5,  0.5, -0.5, 1.0},
						   { -0.5,  0.0, -0.5, 1.0},
						   {  0.0,  0.0,  0.5, 1.0} };
	float* gtVArr[] = {vArr[0], vArr[1], vArr[2], vArr[3]};

	// Ground Truth Face Array
	int fArr[4][4] = {{3,0,1,3},
						{3,2,0,3},
						{3,1,2,3},
						{3,0,1,2}};

	int* gtFArr[4] = {fArr[0],fArr[1],fArr[2],fArr[3]};
	// Ground Truth Color Array
	float** gtCArr = NULL;

	//* Create Test Object *//
	// Creates the .off file
	ofstream file(TESTFILE);
	// Write the pyramid to it
	char pyramid[] = " OFF  \n4\t  4 6 \n 0,5 -0.5 -0.5 \n\t0.5  0.5 \t -0.5 \n -0.5 0.0 -0.5   \t\n0.0 0.0 0.5 \n3 0 1 3 \n3 2 0 3\n3 1 2 3\n3 0 1 2";
	file << pyramid << endl;
	file.close();
	// Load the file into geometry
	Geometry geom = Geometry();
	geom.load(TESTFILE);
	// Delete the file
	remove_test_file(TESTFILE);


	//* Do the test  *//
	// Test numbers
	if(geom.nrVerts() != nrVert)
		failState += 1;

	if( geom.nrFaces() != nrFace )
		failState +=2;

	if( geom.nrLines() != nrLine )
		failState += 4;

	if( geom.colorType() != colorType )
		failState +=8;

	// Test arrays
	if ( !test_vert_loop(&geom, nrVert, gtVArr) )
		failState += 16;
		
	if ( !test_face_loop(&geom, nrFace, gtFArr) )
		failState += 32;
	
	if ( !test_color_loop(&geom, 0, gtCArr) )
		failState += 64;

	if (failState != 0) {
		cout<<"failed."<<endl;
	}else{
		cout<<"success."<<endl;
	}
	return failState;
}


int test_load_OFF_VertColor()
{
	cout << "\tTrying to load a .off file with vertex color info... ";

	int failState = 0;
	
	//* Create Ground Truth *//
	int nrVert = 4, nrFace = 4, nrLine = 6, colorType = 1;	
	// Ground Truth Vertex Array
	float vArr[4][4] = { {  0.5, -0.5, -0.5, 1.0},
						   {  0.5,  0.5, -0.5, 1.0},
						   { -0.5,  0.0, -0.5, 1.0},
						   { 0.0,  0.0,  0.5, 1.0} };
	float* gtVArr[] = {vArr[0], vArr[1], vArr[2], vArr[3]};

	// Ground Truth Face Array
	int fArr[4][4] = {{3,0,1,3},
						{3,2,0,3},
						{3,1,2,3},
						{3,0,1,2}};
	int* gtFArr[4] = {fArr[0],fArr[1],fArr[2],fArr[3]};

	// Ground Truth Color Array
	float cArr[4][4] = {{0.5,0.5,0.5,1.0},
						{0.3,0.3,0.3,1.0},
						{0.6,0.5,0.4,1.0},
						{0.3,0.4,0.5,1.0}};
	float* gtCArr[4] = {cArr[0], cArr[1], cArr[2],cArr[3]};

	//* Create Test Object *//
	// Creates the .off file
	ofstream file(TESTFILE);
	// Write the pyramid to it
	char pyramid[] = "COFF  \n4 4 6 \n 0,5 -0.5 -0.5\t 0.5 0.5 0.5 1.0 \n0.5  0.5 -0.5 \t  0.3 0.3 0.3 1.0  \n -0.5 0.0 -0.5\t  0.6 0.5 0.4 1.0 \t\n 0.0 0.0 0.5 \t 0.3 0.4 0.5 1.0\n3 0 1 3 \n3 2 0 3\n3 1 2 3\n3 0 1 2";
	file << pyramid << endl;
	file.close();
	// Load the file into geometry
	Geometry geom = Geometry();
	geom.load(TESTFILE);
	// Delete the file
	remove_test_file(TESTFILE);


	//* Do the test  *//
	// Test numbers
	if(geom.nrVerts() != nrVert)
		failState += 1;

	if( geom.nrFaces() != nrFace )
		failState +=2;

	if( geom.nrLines() != nrLine )
		failState += 4;

	if( geom.colorType() != colorType )
		failState +=8;

	// Test arrays
	if ( !test_vert_loop(&geom, nrVert, gtVArr) )
		failState += 16;
		
	if ( !test_face_loop(&geom, nrFace, gtFArr) )
		failState += 32;
	
	if ( !test_color_loop(&geom, nrVert, gtCArr) )
		failState += 64;

	if (failState != 0) {
		cout<<"failed."<<endl;
	}else{
		cout<<"success."<<endl;
	}
	return failState;
}
int test_load_OFF_FaceColor()
{
	cout << "\tTrying to load a .off file with face color info... ";
	int failState = 0;
	
	//* Create Ground Truth *//
	int nrVert = 4, nrFace = 4, nrLine = 6, colorType = 2;	
	// Ground Truth Vertex Array
	float vArr[4][4] = { {  0.5, -0.5, -0.5, 1.0},
						   {  0.5,  0.5, -0.5, 1.0},
						   { -0.5,  0.0, -0.5, 1.0},
						   { 0.0,  0.0,  0.5, 1.0} };
	float* gtVArr[] = {vArr[0], vArr[1], vArr[2], vArr[3]};

	// Ground Truth Face Array
	int fArr[4][4] = {{3,0,1,3},
						{3,2,0,3},
						{3,1,2,3},
						{3,0,1,2}};
	int* gtFArr[4] = {fArr[0],fArr[1],fArr[2],fArr[3]};

	// Ground Truth Color Array
	float cArr[4][4] = {{0.5,0.5,0.5,1.0},
						{0.3,0.3,0.3,1.0},
						{0.6,0.5,0.4,1.0},
						{0.3,0.4,0.5,1.0}};
	float* gtCArr[4] = {cArr[0], cArr[1], cArr[2],cArr[3]};

	//* Create Test Object *//
	// Creates the .off file
	ofstream file(TESTFILE);
	// Write the pyramid to it
	char pyramid[] = "OFF  \n4 4 6 \n 0,5 -0.5 -0.5\n0.5  0.5 -0.5 \n -0.5 0.0 -0.5\t\n 0.0 0.0 0.5 \n3 0 1 3 \t 0.5 0.5 0.5 1.0 \n3 2 0 3 \t  0.3 0.3 0.3 1.0  \n3 1 2 3 \t  0.6 0.5 0.4 1.0  \n3 0 1 2 \t 0.3 0.4 0.5 1.0 ";
	file << pyramid << endl;
	file.close();
	// Load the file into geometry
	Geometry geom = Geometry();
	geom.load(TESTFILE);
	// Delete the file
	remove_test_file(TESTFILE);


	//* Do the test  *//
	// Test numbers
	if(geom.nrVerts() != nrVert)
		failState += 1;

	if( geom.nrFaces() != nrFace )
		failState +=2;

	if( geom.nrLines() != nrLine )
		failState += 4;

	if( geom.colorType() != colorType )
		failState +=8;

	// Test arrays
	if ( !test_vert_loop(&geom, nrVert, gtVArr) )
		failState += 16;
		
	if ( !test_face_loop(&geom, nrFace, gtFArr) )
		failState += 32;
	
	if ( !test_color_loop(&geom, nrFace, gtCArr) )
		failState += 64;

	if (failState != 0) {
		cout<<"failed."<<endl;
	}else{
		cout<<"success."<<endl;
	}
	return failState;
}

// Loads an .off file without OFF header.
int test_load_broken_OFF()
{
	cout << "\tTrying to load a broken .off file... ";
	int failState = 0;

	//* Create Test Object without OFF *//
	// Creates the .off file
	ofstream file(TESTFILE);
	// Write the pyramid to it
	char pyramid[] = "boff  \n4 4 6 \n 0,5 -0.5 -0.5\n0.5  0.5 -0.5 \n -0.5 0.0 -0.5\t\n 0.0 0.0 0.5 \n3 0 1 3 \t 0.5 0.5 0.5 1.0 \n3 2 0 3 \t  0.3 0.3 0.3 1.0  \n3 1 2 3 \t  0.6 0.5 0.4 1.0  \n3 0 1 2 \t 0.3 0.4 0.5 1.0 ";
	file << pyramid << endl;
	file.close();
	// Load the file into geometry
	Geometry geom = Geometry();
	geom.load(TESTFILE);

	if (!geom.zombie())
		failState += 1;

	// Delete the file
	remove_test_file(TESTFILE);


	if (failState != 0) {
		cout<<"failed."<<endl;
	}else{
		cout<<"success."<<endl;
	}
	return failState;
}

int main(int argc, const char *argv[])
{
	
	cout << "-= Unit test of class Geometry starting =-"<<endl;
	int i=0,j=0;

	j++;
	if ( test_construct_destruct()==0 )
		i++;

	j++;
	if ( test_load_OFF_NoColor()==0 )
		i++;

	j++;
	if ( test_load_OFF_VertColor()==0 )
		i++;

	j++;
	if ( test_load_OFF_FaceColor()==0 )
		i++;
	
	j++;
	if ( test_load_broken_OFF()==0 )
		i++;


	cout <<"\n\t"<< i << " out of " << j << " tests succeeded." << endl;

	if (i != j) {
		cout << "-= Unit test of class Geometry FAILED =-"<<endl;
 	}else{
		cout << "-= Unit test of class Geometry SUCCEEDED =-"<<endl;
	}
	return 0;
}

