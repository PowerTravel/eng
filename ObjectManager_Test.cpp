#include <iostream>
#include "ObjectManager.h"


// Set up hard-coded comparison objects to see that 
// they match the test object. (should be a pyramid)


// Tests if the class can be created
bool test_new_delete();
// Tests if it can load off files without color info
bool test_load_OFF_NoColor();
// Tests if it can load off files with vertex color
bool test_load_OFF_VertColor();
// Tests if it can load off files with face color
bool test_load_OFF_FaceColor();
// Tests if it notices that the off file is broken
bool test_load_Broken_Off();

using namespace std;
int main(int argc, const char *argv[])
{
	cout << "-= Unit test of class ObjectManager starting =-"<<endl;
	int i=0,j=0;

	if ( !test_new_delete() ) {
		cout << "Failed" << endl;
	}

	if ( test_load_OFF() ) {
		cout << "Failed" << endl;
	}


	cout <<"	"<< i << " out of " << j << " tests succeeded" << endl;
	cout << "-= Unit test of class ObjectManager finnished =-"<<endl;
	return 0;
}



bool test_new_delete()
{	
	cout << "	Testing constructor and destructor..." << endl;
	ObjectManager obj = new ObjectManager();
	
	if (obj.zombie==true) {
		return false;
	}

	delete obj;

	return true;
}

bool test_load_OFF_NoColor()
{

	return false;
}
bool test_load_OFF_VertColor()
{

	return false;
}
bool test_load_OFF_FaceColor()
{

	return false;
}
bool test_load_Broken_Off()
{

	return false;
}
