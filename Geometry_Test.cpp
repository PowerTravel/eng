#include <iostream>
#include "Geometry.h"


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

using namespace std;
int main(int argc, const char *argv[])
{
	
	cout << "-= Unit test of class Geometry starting =-"<<endl;
	int i=0,j=0;
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

bool test2_load_OFF_NoColor()
{
	cout << "\tTrying to load a .off file without color info... ";



	cout << "failed." << endl;
	return false;
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
