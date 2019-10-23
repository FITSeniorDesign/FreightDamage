//============================================================================
// Name        : PlacementAlgo.h
// Author      : Chad Boyer (cboyer2016@my.fit.edu)
//				 William Ferrick (wferrick2016@my.fit.edu)
//				 Jordan Murray (jmurray2016@my.fit.edu)
//				 Connor Roth (croth2016@my.fit.edu)
// Description : Header file for PlacementAlgo.cpp
//============================================================================

#ifndef PLACEMENTALGO_H_
#define PLACEMENTALGO_H_

// Include all packages
#include <vector>

// Create a Package Class
class Package{

// Declare all attributes as private
private:
	int iD;
	int weight;
	int height;
	int length;
	int width;
	int fragility;
	std::vector<int> location;

// Declare all functions as public
public:
	int getID();
	void setID(int);
	int getWeight();
	void setWeight(int);
	int getHeight();
	void setHeight(int);
	int getLength();
	void setLength(int);
	int getWidth();
	void setWidth(int);
	int getFragility();
	void setFragility(int);
	void swapLengthAndWidth();
	std::vector<int> getLocation();
	void setLocation(std::vector<int>);
	Package(int, int, int, int, int, int);
	int findVolume();
};

// Create a Trailer Class
class Trailer {

// Declare all attributes as private
private:
	// Trailer broken up over half a foot
	const static int length = 5;	// 53
	const static int width = 5;		// 8.5
	const static int height = 5;	// 13
	int volume = length * width * height;

//Declare all functions as public
public:
	int simulation [length][width][height];
	void updateSimulation ();
	int getLength();
	void setLength(int);
	int getWidth();
	void setWidth(int);
	int getHeight();
	void setHeight(int);
	int findVolume();
	void placePackage(Package);
	Trailer();
	void printTrailer();
	void findOpenLocation();
	std::vector<int> findLocation(Package, bool);
};

// Determine where the package should go
Trailer pickNext(std::vector<Package>, int);

#endif /* PLACEMENTALGO_H_ */
