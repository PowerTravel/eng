#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Geometry.h"

/*
// Create comparison object
float** create_referenceGeom();
bool create_test_off_NoColor(const char* filename);
bool remove_test_file(const char* filename);
// Tests if the class can be created
bool test1_new_delete();
// Tests if it can load off files without color info
bool test2_load_OFF_NoColor();
// Tests if it can load off files with vertex color
bool test3_load_OFF_VertColor();
// Tests if it can load off files with face color
bool test4_load_OFF_FaceColor();
// Tests if it notices that the off file is broken
bool test5_load_broken_OFF();
*/

// Global name for testfile
const char TESTFILE[] = "pyramidTest.off";

using namespace std;


// Create test .off file and supplies ground truth
Geometry create_test_off_NoColor(const char* filename)
{
	// Creates the .off file
	ofstream file(filename);

	char pyramid[] = " OFF  \n4\t  4 6 \n 0,5 -0.5 -0.5 \n\t0.5  0.5 \t -0.5\n -0.5 0.0 -0.5  \n0.0 0.0 0.5 \n3 0 1 3 \n3 2 0 3\n3 1 2 3\n3 0 1 2";
	file << pyramid << endl;
	file.close();
	
	// Creates GroundTruth
	int nrVert = 4;
	int nrFace = 4;
	int nrLine = 6;

	tVl[0][0] = 0.5; tVl[0][1] = -0.5;tVl[0][2] = -0.5;
	tVl[1][0] = 0.5; tVl[1][1] = 0.5; tVl[1][2] = -0.5;
	tVl[2][0] = -0.5;tVl[2][1] = 0.0; tVl[2][2] = -0.5;
	tVl[3][0] = 0.0; tVl[3][1] = 0.0; tVl[3][2] = 0.5;

	tF1[0][0] = 3; tF1[0][1] = 0; tF1[0][2] = 1; tF1[0][3] = 3;	
	tF1[1][0] = 3; tF1[1][1] = 2; tF1[1][2] = 0; tF1[1][3] = 3;	
	tF1[2][0] = 3; tF1[2][1] = 1; tF1[2][2] = 2; tF1[2][3] = 3;	
	tF1[3][0] = 3; tF1[3][1] = 0; tF1[3][2] = 1; tF1[3][3] = 2;	

	Geometry gtGeom = Geometry();
}

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
bool test1_new_delete()
{	
	cout << "\tTesting constructor and destructor... ";
	
	for(int i=0; i<10; i++)
	{
		Geometry geom = Geometry();
		if( geom.id() != i)
		{
			cout << "failed."<<endl;
			return false;
		}
	}

	cout << "done." << endl;
	return true;
}

void get_list_from_geom(Geometry* geom,int* nrVert,float** vl,int*  nrFace, int** fl, int* nrLine, int* colorType, float** cd)
{

}

void create_ground_truth_geom(void (ground_truth_fun)(const char, ) )
{

}

int test_geom_compare_fun()
{	
	int failFlag = 0;

	
}


bool test2_load_OFF_NoColor()
{
	cout << "\tTrying to load a .off file without color info... ";
	
	int failFlag = 0;

	// Declare Ground Truth Variables
	int gtNrVert=0, gtNrFace=0, gtNrLine=0,  gtColorType=-1;
	float** gtVl = NULL;
	int** gtFl = NULL;
	float** gtCl = NULL;

	// Declare Test Variables
	int nrVert=0, nrFace=0, nrLine=0, colorType=-1;
	float** vl = NULL;
	int** fl = NULL;
	float** cl = NULL;

	create_test_off_NoColor(TESTFILE, &gtNrVert, gtV1, &gtNrFace, gtFl, &gtNrLine, &gtColorType, gtCl)
	
	Geometry geom = Geometry();
	geom.load(TESTFILE);

	

	get_list_from_geom(geom, nrVert, vl, nrFace, fl, nrLine, colorType, cd);

	

	// Get the list and nr of vertecies
	int vlnr = geom.getNrVerts(vl);
	float** vl = NULL;
	geom.getVertList(vl);

	// Get the list and nr of faces.	
	int flnr = geom.getNrFaces();
	int** fl = NULL;
	geom.getFaceList(fl);

	// Get the colortype and the colorlist (should be null)
	int coloType = geom.getColorType();
	float** cl = NULL;
	geom.getColorList(cl);

	get_geom_data(&nrVert, vl, &nrFace, fl, &nrLine, &colorType, cl);	

	// Check that the number of vertex, faces and colors are ok
	if(vlnr != 8){
		failFlag += 1;
	}else if(flnr != 8){
		failFlag += 2;
	}else if(colorType != 0){
		failFlag += 4;
	}else if(colorList != NULL ){
		failFlag += 8;
	}

	bool vertFailFlag = false;
	bool faceFailFlag = false;
	for (int i=0; i<4; i++ )
	{
		for	(int j=0; j<3; j++)
		{
			if ( vl[i][j]!=trueVl[i][j] )
			{
				vertFailFlag = true;
			}
		}
		
		for (int j = 0; j<4; j++)
		{
			if ( fl[i][0]!=trueFl[i][0] )
			{
				faceFailFlag = true;
			}	
		}
	}
	remove_test_file(TESTFILE);
	cout << "failed." << endl;
	return false;
}

// Tests the equal function in geom.
int testEqual()
{
	int nrVert=-1, nrFace=-1, colorType-10; 
	float** trueVl = NULL;
	int** trueFl = NULL; 
	float** trueCl = NULL;
	// Get ground truth we can compare against
	getPyramidGroundTruth( &nrVert, trueVl, &nrFace , trueFl, &colorType, trueCl);

	// Create a geom containing groundtruth
	Geometry gtGeom(treVl, trueFl, trueCl);
}


bool test3_load_OFF_VertColor()
{
	cout << "\tTrying to load a .off file with vertex color info... ";
	

	cout << "failed." << endl;
	return false;
}
bool test4_load_OFF_FaceColor()
{
	cout << "\tTrying to load a .off file with face color info... ";

	cout << "failed." << endl;
	return false;
}
bool test5_load_broken_OFF()
{
	cout << "\tTrying to load a broken .off file... ";

	cout << "failed." << endl;
	return false;
}

float** create_referenceGeom()
{
	// Allocate space for a reference-pyramid
	//float** geom_ref = new (float*)[9];
	return NULL;
}

int main(int argc, const char *argv[])
{
	
	cout << "-= Unit test of class Geometry starting =-"<<endl;
	int i=0,j=0;

	/*
	test constructor // destructor
	test geoms compare-funk
	
	test everything else by creating a ground-truth geom and comparing with a
	geom loaded from object.
	
	*/


	j++;
	if ( test1_new_delete() ) {
		i++;
	}

	j++;
	if ( test2_load_OFF_NoColor() ) {
		i++;
	}

	j++;
	if ( test3_load_OFF_VertColor() ) {
		i++;
	}

	j++;
	if ( test4_load_OFF_FaceColor() ) {
		i++;
	}

	j++;
	if ( test5_load_broken_OFF() ) {
		i++;
	}


	cout <<"\n\t"<< i << " out of " << j << " tests succeeded." << endl;

	if (i != j) {
		cout << "-= Unit test of class Geometry FAILED =-"<<endl;
 	}else{
		cout << "-= Unit test of class Geometry SUCCEEDED =-"<<endl;
	}
	return 0;
}

