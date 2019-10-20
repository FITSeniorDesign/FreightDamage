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
};

// Create a Trailer Class
class Trailer {
private:
	// Trailer broken up over half a foot
	int length = 106;
	int width = 17;
	int height = 26;
public:
	void updateSimulation ();
	int getLength();
	void setLength(int);
	int getWidth();
	void setWidth(int);
	int getHeight();
	void setHeight(int);
	Trailer (int, int, int);
	void constructSimulation();
};

// Place the packages
void placement(std::vector<Package>);


#endif /* PLACEMENTALGO_H_ */
