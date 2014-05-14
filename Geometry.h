#ifndef GEOMETRY_H
#define GEOMETRY_H


// Geometry class, Holds geometry data
// Can load off files and at some later
// pointa also other types of files
class Geometry
{
	public:

		Geometry();
		virtual ~Geometry();

		// Getters:
		int id();		// The objects ID
		bool zombie();	// The objects zombie-status
	private:

		// Data members have a m before their name to differentiate them from functions.

		// Id for objects
		static unsigned long int mid_inc;
		unsigned long int mid;
		
		// Flag if the object is working properly
		bool mzombie;
};

#endif // GEOMETRY_h
