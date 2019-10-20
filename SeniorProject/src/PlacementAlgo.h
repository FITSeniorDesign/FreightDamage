/*
 * PlacementAlgo.h
 *
 *  Created on: Oct 19, 2019
 *      Author: elcha
 */


#ifndef PLACEMENTALGO_H_
#define PLACEMENTALGO_H_

#include <fstream>
#include <iostream>
#include <vector>

class Package{
private:
	int packageNumber;
	int weight;
	int height;
	int length;
	int width;
	int fragility;
	std::string description;
public:
	int getPackageNumber();
	void setPackageNumber(int);
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

void placement(std::vector<Package>);


#endif /* PLACEMENTALGO_H_ */
