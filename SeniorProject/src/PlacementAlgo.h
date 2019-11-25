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
	bool isPallet;

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
	void setIsPallet(bool);
	bool getIsPallet();
	void setFragility(int);
	void swapLengthAndWidth();
	void swapLengthAndHeight();
	void swapHeightAndWidth();
	std::vector<int> getLocation();
	void setLocation(std::vector<int>);
	Package(int, int, int, int, int, int, bool);
	int findVolume();
};

// Create a Trailer Class
class Trailer {

// Declare all attributes as private
private:
	// Trailer broken up over half a foot
	const static int length = 10;	// 53
	const static int width = 10;		// 8.5
	const static int height = 10;	// 13
	int volume = (length) * (width) * (height);
	std::vector<Package> placedPackages;

//Declare all functions as public
public:
	int weightedTrailer [length][width][height];				// 3D trailer in computing the weight of locations
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
	std::vector<int> palletLocation(Package&);
	std::vector<int> crateLocation(Package&);
	std::vector<int> findLocation(Package);
	int furthestBack(Package, Package, std::vector<int>, std::vector<int>);
	bool touchesWall(Package, std::vector<int>);
	std::vector<int> determineBest(Package&, Package, std::vector<int>, std::vector<int>);
	bool fitPackage(int, int, int, Package);
};

// Determine where the package should go
Trailer pickNext(std::vector<Package>, int);

#endif /* PLACEMENTALGO_H_ */
