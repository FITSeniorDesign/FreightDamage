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
	std::string description;
// Declare all functions as private
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
	std::string getDescription();
	void setDescription(std::string);
	Package();
	Package(int, int, int, int, int, int);
	int findVolume();
};

// Create a Trailer Class
class Trailer {
private:
	// Trailer broken up over half a foot
	const static int length = 53;
	const static int width = 8;
	const static int height = 13;
	int volume = length * width * height;
	int simulation [length][width][height];
public:
	void updateSimulation ();
	int getLength();
	void setLength(int);
	int getWidth();
	void setWidth(int);
	int getHeight();
	void setHeight(int);
	int findVolume();
	//void lowerVolume();
	//int findVolume();
	Trailer();
	void findOpenLocation();
	int* findLocation(Package);
};

// Place the packages
void placement(std::vector<Package>);


#endif /* PLACEMENTALGO_H_ */
