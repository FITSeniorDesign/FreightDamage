//============================================================================
// Name:		 PlacementAlgo.cpp
// Author:		 Chad Boyer (cboyer2016@my.fit.edu)
//				 William Ferrick (wferrick2016@my.fit.edu)
//				 Jordan Murray (jmurray2016@my.fit.edu)
//				 Connor Roth (croth2016@my.fit.edu)
// Description:	 Source file to place Packages into a Trailer
//============================================================================

// Include all packages
#include <iostream>
#include <string>
#include <algorithm>

// Include the function headers
#include "PlacementAlgo.h"

// Declare used namespace
using namespace std;



// Package getter functions for each attribute
int Package::getFragility() {	return this->fragility;	}

int Package::getHeight() {	return this->height;	}

int Package::getLength() {	return this->length;	}

int Package::getID() {	return this->iD;	}

int Package::getWeight() {	return this->weight;	}

int Package::getWidth() {	return this->width;	}

vector<int> Package::getLocation() {	return location;	}

bool Package::getIsPallet() {	return this->isPallet;	}

// Package setter functions for each attribute
void Package::setFragility(int fragility) {	this->fragility = fragility;	}

void Package::setHeight(int height) {	this->height = height;	}

void Package::setLength(int length) {	this->length = length;	}

void Package::setID(int iD) {	this->iD = iD;	}

void Package::setWeight(int weight) {	this->weight = weight;	}

void Package::setWidth(int width) {	this->width = width;	}

void Package::setLocation(vector<int> location) {	this->location = location;	}

void Package::setIsPallet(bool isPallet) {	this->isPallet = isPallet;	}

/*
 * Function: 	swapLengthAndWidth
 * Description: Used to check if the package will fit turned 90 degrees
 * Parameters: 	none
 * Returns:		none
 */
void Package::swapLengthAndWidth(){
	int temp = length;
	length = width;
	width = temp;
}

/*
 * Function: 	swapLengthAndHeight
 * Description: Used to check if the package will fit turned 90 degrees
 * Parameters: 	none
 * Returns:		none
 */
void Package::swapLengthAndHeight(){
	int temp = length;
	length = height;
	height = temp;
}

/*
 * Function: 	swapHeightAndWidth
 * Description: Used to check if the package will fit turned 90 degrees
 * Parameters: 	none
 * Returns:		none
 */
void Package::swapHeightAndWidth(){
	int temp = height;
	height = width;
	width = temp;
}



/*
 * Function: 	findVolume
 * Description: Used to return the volume of the package
 * Parameters: 	none
 * Returns:		none
 */
int Package::findVolume() {	return length * width * height;	}

/*
 * Function: 	Package
 * Description: Used to construct a Package object
 * Parameters: 	iD, the ID of the package
 *             	weight, the weight of the package
 *             	length, the length of the package
 *             	width, the width of the package
 *             	height, the height of the package
 *             	fragility, the fragility of the package
 * Returns:		none
 */
Package::Package(int iD, int weight, int length, int width, int height, int fragility, bool isPallet) {
	// Call setter functions called on each attribute
	setID(iD);					// Set the ID of the package
	setWeight(weight);			// Set the Weight of the package
	setLength(length);			// Set the Length of the package
	setWidth(width);			// Set the Width of the package
	setHeight(height);			// Set the Height of the apckage
	setFragility(fragility);	// Set the Fragility of the package
	setIsPallet(isPallet);		// Set the packaging type
}

Package::Package(){

}


// Trailer getter functions for each attribute
int Trailer::getHeight() {	return this->height;	}

int Trailer::getLength() {	return this->length;	}

int Trailer::getWidth() {	return this->width;		}

int Trailer::findVolume() {	return this->volume;	}

/*
 * Function: 	Trailer
 * Description: Used to construct a Trailer object
 * Parameters: 	none
 * Returns:		none
 */
Trailer::Trailer() {
	/*for (int i = 0; i < this->length; i++)				// Iterate over the length of the truck
		for (int j = 0; j < this->width; j++)			// Iterate over the width of the truck
			for (int k = 0; k < this->height; k++)		// Iterate over the height of the truck
				weightedTrailer[i][j][k] = 0;			// Initialize each element to 0
*/
}

/*
 * Function: 	fitLocation
 * Description: Iterate over the packages dimensions to see
 * 				if it fits
 * Parameters: 	package, trying to be placed into the trailer
 * Returns:		true, package does fit
 * 				false, package does not fit
 */
bool Trailer::fitPackage(int height, int length, int width, Package package) {
	if ((width + package.getWidth() <= this->width) &&						// Check that the package doesnt go over the bounds of the trailer
		(height + package.getHeight() <= this->height) &&
		(length + package.getLength() <= this->length)) {

		// Check if the package fits
		for (int i = 0; i < package.getHeight(); i++)						// Iterate over the packages height
			for (int j = 0; j < package.getLength(); j++)					// Iterate over the packages length
				for(int k = 0; k < package.getWidth(); k++)					// Iterate over the packages width
					for (Package a : this->placedPackages) {				// Iterate over the currently placed packages
						vector <int> aLocation = a.getLocation();			// Get the location of the current package
						if ((aLocation[0] == height+i) || ((aLocation[0] < height+i)		// The height is taken or ranges into the location
								&& (aLocation[0] + a.getHeight() > height+i)))
							if ((aLocation[1] == length+j) || ((aLocation[1] < length+j)	// The length is taken or ranges into the location
									&& (aLocation[1] + a.getLength() > length+j)))
								if ((aLocation[2] == width+k) || ((aLocation[2] < width+k)	// The width is taken or ranges into the location
										&& (aLocation[2] + a.getWidth() > width+k)))
									return false;							// The package doesn't fit
					}
	} else		return false;												// The package does not fit
	return true;															// The package fits
}

/*
 * Function: 	findLocation
 * Description: Used to find an open location for a package in the truck
 * 				based off the location of other packages.
 * Parameters: 	package, trying to be placed into the trailer
 * Returns:		location of the package in the trailer
 */
vector <int> Trailer::findLocation(Package package) {
	vector <int> location;														// Location where package should go

	// See if the package will fit
	for (int height = 0; height < this->height; height++)						// Iterate over the height of the trailer
		for (int length = 0; length < this->length; length++)					// Iterate over the length of the trailer
			for (int width = 0; width < this->width; width++) {					// Iterate over the width of the trailer
				bool fits = true;												// Boolean to show there is a fill or not

				// Check if the package fits around the other packages
				for (Package a : this->placedPackages) {						// Iterate over all placed packages
					vector <int> aLocation = a.getLocation();					// Get the location of the current package
					if ((aLocation[2] == width && aLocation[1] == length &&		// The current location is filled
							aLocation[0] == height)) {
						fits = false;											// The package does not fit here
						break;													// Break out of the loop and
					}
				}
				if (fits && fitPackage(height, length, width, package)) {		// The package fits into the trailer
					location.push_back(height);									// Save the height first
					location.push_back(length);									// Save the length second
					location.push_back(width);									// Save the width third
					return location;											// Return the dimensions of the trailer
				}
			}
	return location;															// Return the location found and empty if no spot
}

/*
 * Function: 	placePackage
 * Description: Used to put the package in the truck at the location
 * Parameters: 	package, placed into the trailer
 * Returns:		none
 */
void Trailer::placePackage(Package package) {
	// Place a package in the weighted trailer
	/*for(int height = 0; height < package.getHeight(); height++)			// Iterate over the length
		for(int length = 0; length < package.getLength(); length++)			// Iterate over the width
			for(int width = 0; width < package.getWidth(); width++)			// Iterate over the height
				this->weightedTrailer[(package.getLocation())[0] + height]	// Set the package ID in the trailer
						   [(package.getLocation())[1] + length]
						   [(package.getLocation())[2] + width]
							= package.getID();
*/
	this->volume -= package.findVolume();									// Deduct the volume of the package from the overall volume of the trailer
	this->placedPackages.push_back(package);								// Save the package as placed in the trailer
}

/*
 *
 */
void Trailer::removePackage(Package package) {
	this->volume += package.findVolume();									// Deduct the volume of the package from the overall volume of the trailer
	this->placedPackages.pop_back();										// Delete the last item from the list

	//this->placedPackages.erase(std::remove(this->placedPackages.begin(), this->placedPackages.end(), package), this->placedPackages.end());
	//this->placedPackages.push_back(package);								// Save the package as placed in the trailer
}

/*
 * Function: 	touchesWall
 * Description: Used to determine if a package touches the wall
 * Parameters: 	package, placed into the trailer
 * 				package, the dimensions fo the package
 * 				location, the location of the package
 * Returns:		true if touches two+ walls, falsoe otherwise
 */
bool Trailer::touchesWall (Package package, std::vector<int> location) {
	// Check if the first is against a wall is against a wall
	bool width = false;															// The package touches the wall
	bool length = false;														// The package touches the wall
	bool height = false;														// The package touches the wall

	if (location[0] == 0 || (location[0] + package.getHeight() == this->height))// The package is against the height limit
		height = true;															// The package touches the height
	if (location[1] == 0 || (location[1] + package.getLength() == this->length))// The package is against the length limit
		length = true;															// The package touches the length
	if (location[2] == 0 || (location[2] + package.getWidth() == this->width))	// The package is against the width limit
		width = true;															// The package touches the width

	if ((width && length) || (width & height) || (length && height))			// Two of the three walls are touched
		return true;															// The package does touch the wall
	return false;																// The package does not touch the wall
}

/*
 * Function: 	furthestBack
 * Description: Used to determine the furthest back location
 * Parameters: 	dimensionsA, dimensions of the first location
 * 				dimensionsB, dimensions of the second location
 * 				a, first location in the trailer
 * 				b, second location in the trailer
 * Returns:		the compare value, negative means take b, otherwise take a
 */
int Trailer::furthestBack(Package dimensionsA, Package dimensionsB, std::vector<int> a, std::vector<int> b) {
	char compare = 0;												// Used to determine which location to use

	// Check if the height first, then the length second, and the width third
	if (a[0] < b[0]) 					compare--;					// The first location is better
	else if (a[0] > b[0])				compare++;					// The second location is better
	else if (a[0] == b[0]) {										// The packages are at the same height
		if (a[1] > b[1])				compare--;					// The first location is better
		else if (a[1] < b[1])			compare++;					// The second location is better
		else if (a[1] == b[1]) {									// The packages are the same length
			if (a[2] > b[2])			compare--;					// The first location is better
			else if (a[2] < b[2])		compare++;					// The second location is better
		}
	}

	if (compare == 0) {												// The two locations are the same
		if (dimensionsA.getLength() < dimensionsB.getLength())		// A is the better length
			compare++;												// Compare leans towards A
		else														// B is the better location
			compare--;												// Compare leans towards B
	}

	// Check if the first is against a wall is against a wall
	//if (touchesWall(dimensionsA, a)) 	compare++;					// Check if the first package touches two walls
	//if (touchesWall(dimensionsB, b))	compare--;					// Check if the second package touches two walls


	// Determine which one to use
	return compare;													// Return the compare value

}

/*
 * Function: 	determineBest
 * Description: Used to determine the better location in the truck
 * Parameters: 	dimensionsA, dimensions for the first location
 * 				dimensionsB, dimensions for the second location
 * 				locationA, first location in the trailer
 * 				locationB, second location in the trailer
 * Returns:		the best location
 */
std::vector<int> Trailer::determineBest(Package &dimensionA, Package dimensionB, std::vector<int> locationA, std::vector<int> locationB) {
	if (locationA.size() == 0 && locationB.size() != 0) {										// If there is not a location found before
		locationA = locationB;																	// Save the location in the first spot
		dimensionA = dimensionB;																// Move the dimensions into dimensionA
	} else if (locationB.size() != 0 && locationA.size() != 0)									// The locations are found and not the same
		if (this->furthestBack(dimensionA, dimensionB, locationA, locationB) < 0) {				// Check which is the better placement
			dimensionA = dimensionB;															// Save the new pallet dimensions
			locationA = locationB;																// Save the better location
		}
	return locationA;																			// Return the best location in the trailer
}

/*
 * Function: 	palletLocation
 * Description: Used to rotate the pallet correctly
 * Parameters: 	pallet, Package to be rotated
 * Returns:		the location in the trailer
 */
std::vector <int> Trailer::palletLocation(Package &pallet) {
	vector <int> locationA = this->findLocation(pallet);									// Test the packages current dimensions for a spot (LWH)
	Package dimensionA = pallet;															// Used for the first dimension of the pallet

	pallet.swapLengthAndWidth();															// Rotate the Package's Length and Width (WLH)
	locationA = determineBest(dimensionA, pallet, locationA, this->findLocation(pallet));	// determine the best placement in the trailer

	pallet = dimensionA;																	// Update the pallet before returning it
	return locationA;																		// Return the furthest back location
}

/*
 * Function: 	crateLocation
 * Description: Used to rotate the crate correctly
 * Parameters: 	crate, Package to be rotated
 * Returns:		the locationin the trailer
 */
std::vector <int> Trailer::crateLocation(Package &crate) {
	Package dimensionA = crate;																// Save the original dimensions of the package
	vector <int> locationA = palletLocation(crate);											// Check if rotation like a pallet will work (LWH, WLH)

	if (dimensionA.getHeight() == crate.getHeight()											// Check if the dimensions changed or not
			&& dimensionA.getLength() == crate.getLength()
			&& dimensionA.getWidth() == crate.getWidth())
		crate.swapLengthAndWidth();															// Rotate the Package's Length and Width (WLH)


	crate.swapHeightAndWidth();																// Rotate the Package's Height and Width (WHL)
	vector <int> locationB = this->findLocation(crate);										// Test the packages current dimensions for a spot
	locationA = determineBest(dimensionA, crate, locationA, this->findLocation(crate));		// determine the best placement in the trailer

	crate.swapLengthAndWidth();																// Rotate the Package's Length and Width (HWL)
	locationA = determineBest(dimensionA, crate, locationA, this->findLocation(crate));		// determine the best placement in the trailer

	crate.swapHeightAndWidth();																// Rotate the Package's Height and Width (HLW)
	locationA = determineBest(dimensionA, crate, locationA, this->findLocation(crate));		// determine the best placement in the trailer

	crate.swapLengthAndWidth();																// Rotate the Package's Length and Width (LHW)
	locationA = determineBest(dimensionA, crate, locationA, this->findLocation(crate));		// determine the best placement in the trailer

	crate = dimensionA;																		// Save the dimensions of the crate
	return locationA;																		// Return the best location of the
}

/*
 * Function: 	printTrailer
 * Description: Used to print the 3D array of the trailer
 * Parameters:	none
 * Returns:		none
 */
void Trailer::printTrailer() {
	cout << "Trailer Contents" << endl << "[H][L][W] (h, l, w) = Package ID" << endl;
	for (Package a : this->placedPackages)
		cout << "[" << a.getLocation()[0] << "][" << a.getLocation()[1] << "][" << a.getLocation()[2]
			 << "] (" << a.getHeight() << ", " << a.getLength() << ", " << a.getWidth() << ")"
			 << " = " << a.getID() << endl;
}



/*
 * Function:	heapify
 * Description:	Used to sort the min heap based off of the key
 * Parameters:	heap, a pointer to a vector of Packages
 * 				index, location of where to sort the heap.
 * Returns:		none
 */
void heapify (vector<Package> *heap, int index) {
	int largest = index;								// Find the parent
	int left = 2 * index + 1;							// Find the left child
	int right = 2 * index + 2;							// Find the right child

	// Check if the left child is greater than the parent based off key
	if (left < (int)heap->size() && (*heap)[left].getFragility() < (*heap)[largest].getFragility())
		largest = left;

	// Check if the right child is greater than the parent based off key
	if (right < (int)heap->size() && (*heap)[right].getFragility() < (*heap)[largest].getFragility())
		largest = right;

	// Check if the parent has moved
	if (largest != index) {

		// Swap the parent and the child
		Package temp = (*heap)[largest];
		(*heap)[largest] = (*heap)[index];
		(*heap)[index] = temp;

		// Heapify the list again on the child
		heapify (heap, largest);
	}

}

/*
 * Function: removeMin
 * Description: Used to remove the top key from the min heap
 * Parameters: heap, a pointer to a vector of Packages
 */
Package removeMin(vector <Package> *heap) {
	Package popped = (*heap)[0];						// Save the top element
	(*heap)[0] = (*heap)[(*heap).size() - 1];			// Move the last element to the top
	(*heap).pop_back();									// Remove the last element from the heap
	heapify(heap, 0);									// Heapify the entire heap
	return popped;										// Return the removed element
}

/*
 * Function: makeHeap
 * Description: Used to construct the min heap using a vector
 * Parameters: heap, a pointer to a vector of Packages
 */
void makeHeap(vector<Package> *heap) {
	int lastNonLeaf = (heap->size()/2) - 1;				// Find the last location of a non-leaf in the vector

	for (int i = lastNonLeaf; i >= 0; i--)				// Iterate over all non-leaves
		heapify (heap, i);								// Create a min heap on the non-leaves
}

/*
 * Function: 	compareWeight
 * Description: Used to determine the secondary factor of Packages
 * Parameters:  a, Package one
 * 				b, Package two
 * Returns:		1 means place Package two first
 * 				-1 means place Package one first
 * 				0 means weights are equal
 */
int compareWeight(Package a, Package b) {
	if (a.getWeight() > b.getWeight())					// Package 1 weighs more than Package 2
		return -1;										// Shows the packafe a has precedence
	else if (a.getWeight() < b.getWeight())				// Package 2 weighs more than Package 1
		return 1;										// Returns package b has precedence
	else												// The packages are equal in weight
		return 0;										// Package weight are equal, don't influence the final total
}

/*
 * Function: 	compareSecondary
 * Description: If there is a collision, determine what should be placed first
 * Parameters: 	collision, pointer to a list of package collisions based on fragility
 * 				trailer, the location of where a package can be placed
 * Returns:		none
 */
void compareSecondary (vector <Package> *collision, Trailer *trailer){
	for (int i = 1; i < (int)(*collision).size(); i++) {								// Iterate over all packages with a collision, starting at the second package

		char compare = 0;																// Used to determine a package swap

		// Check if the volumes of both fit in the truck
		if ((*trailer).findVolume() > (*collision)[0].findVolume()) {					// Determine if the volume fits

			if ((*collision).front().getIsPallet())												// Finding the location for a pallet
				(*collision).front().setLocation(trailer->palletLocation((*collision).front()));	// Find if the pallet fits
			else																				// Finding the location for a crate
				(*collision).front().setLocation(trailer->crateLocation((*collision).front()));	// Find if the crate fits

			if ((*collision).front().getLocation().size() == 0)	compare ++;				// The location is not found
			else 												compare --;				// The location is found
		}

		if ((*trailer).findVolume() > (*collision)[i].findVolume()) {					// Determine if the volume fits

			if ((*collision).front().getIsPallet())										// Finding the location for a pallet
				(*collision)[i].setLocation(trailer->palletLocation((*collision)[i]));	// Find if the pallet fits
			else																		// Finding the location for a crate
				(*collision)[i].setLocation(trailer->crateLocation((*collision)[i]));	// Find if the crate fits

			if (compare == 1 && (*collision)[i].getLocation().size() == 0)	continue;	// Neither package fits, skip
			else if ((*collision)[i].getLocation().size() == 0)	compare ++;				// The location is not found
			else if ((*collision)[i].getLocation().size() != 0)	compare --;				// The location is found

		}

		// Add extreme dimension variable


		// Both packages fit
		if (compare == 0)	compare += compareWeight((*collision).front(), (*collision)[i]);	// Check the weight against each other

		if (compare == 0)	continue;				// If the two packages are equal, keep the current with lower fragility
		else if (compare > 0) {						// The second package should be placed first
			// Swap the two packages
			Package temp = (*collision).front();
			(*collision).front() = (*collision)[i];
			(*collision)[i] = temp;
		}

	}
}

Trailer pickNextRecursive (Trailer trailer, vector<Package> manifest, int diff) {
	/// Trailer object is passed in, use that
	std::cout.flush();
	makeHeap(&manifest);			// Create a heap of the remaining packages

	if (manifest.size() != 0) {										// There are still packages in the manifest
		//int used = 0;
		//Package arrayCol [3];									// Vector of all the collisions

		//Package arrayCol[3];
		vector <Package> collision;
		collision.push_back(removeMin(&manifest));
		//collision					// Take the top element of the heap
		//used++;

		for (int i = 0; i < manifest.size(); i++) {
			cout << manifest[i].getID() << ", " << endl;
		}

		while (manifest.size() > 0 && abs(manifest.front()			// Check if there is collision based off of diff
				.getFragility() - collision[0]
				.getFragility()) <= diff)
			collision.push_back((removeMin(&manifest)));				// Add the package to the end of the list

		for (int i = 0; i < collision.size(); i++) {
			cout << collision[i].getID() << ", " << endl;
		}

		// If there is a collision
		if (collision.size() > 1) {
			//compareSecondary(&collision, &trailer);					// Determine the next package to place in the truck

			for (int w = 0, size = collision.size(); w < size; w++)	{		// Iterate over all the unused packages
				compareSecondary(&collision, &trailer);				// Determine the next package to place in the truck

				trailer.placePackage(collision.front());				// Place the package

				cout << "Placing package: " << collision.front().getID() << endl;		// TESTING

				//vector <Package> heapCollision;
				// Add the unused packages to the end
				//for (int i = 0; i < collision.size() - 1; i++) {
				//	cout << collision[i].getID() << ", " << endl;
					//manifest.push_back(removeMin(collision));
					//manifest.push_back(collision.pop_back());
				//}

				for (int i = 1; i < collision.size(); i++) {
					manifest.push_back(collision.at(i));
					cout << collision.at(i).getID() << ", " << endl;
				}


				//manifest.insert(manifest.end(), collision.begin() + 1,	// Add the unplaced packages back to the manifest
				//		collision.end());

				pickNextRecursive(trailer, manifest, diff);			// Create a trailer with the remaining packages

				trailer.removePackage(collision.front());					// Remove the package from the trailer

				cout << "Picking up package: " << collision.front().getID() << endl;	// TESTING

				(collision).front().getLocation().clear();			// Clear the location

				manifest.push_back(collision.at(0));
				cout << (manifest.at((int)manifest.size() - 1).getID()) << endl;
				//manifest.insert(manifest.end(), collision.begin(),	// Add the placed package back to the manifest
				//		collision.begin()+1);

				for (int i = 0; i < manifest.size(); i++) {
					cout << manifest.at(i).getID() << ", " << endl;
				}


				//auto temp = collision.at(0);
				//auto tempLast =
				//collision[0] = collision[(int)collision.size() - 1];
				//collision.pop_back();
				//}

				for (int i = 0; i < manifest.size(); i++) {
					cout << manifest.at(i).getID() << ", " << endl;
				}
				//collision[w].getLocation().clear();					// Remove the locations of the unplaced packages
			}
			//manifest.insert(manifest.end(), collision.begin() + 1,	// Add the unplaced packages back to the manifest
			//		collision.end());
			//makeHeap(&manifest);									// Generate the heap again

		} else {
			if ((collision).front().getIsPallet())												// Finding the location for a pallet
				(collision).front().setLocation(trailer.palletLocation((collision).front()));	// Find if the pallet fits
			else																				// Finding the location for a crate
				(collision).front().setLocation(trailer.crateLocation((collision).front()));	// Find if the crate fits

			//if (collision.front().getLocation().size() != 0)		// If there is not a location
			//	continue;											// Move to the next package
			//int manifestSize = manifest.size();

			trailer.placePackage(collision.front());

			cout << "Placing package: " << collision.front().getID() << endl;

			pickNextRecursive(trailer, manifest, diff);

			trailer.removePackage(collision.front());

			cout << "Picking up package: " << collision.front().getID() << endl;

			(collision).front().getLocation().clear();

			manifest.insert(manifest.end(), collision.begin(),	// Add the placed package back to the manifest
					collision.begin()+1);

			//manifest.erase(manifest.end()-collision.size()-2, manifest.end());

			//if (collision.front().getLocation().size() == 0)		// If there is not a location
			//	continue;											// Move to the next package
		}

	} else {
		cout << "The packages placed were:" << endl;
		for (int i = 0; i < (int)trailer.placedPackages.size(); i++) {
			cout << trailer.placedPackages[i].getID() << ", " << endl;
		}
	}

	return trailer;


}

/*
 * Function:	pickNext
 * Description: Used to determine how items are placed in the trailer.
 * Parameters:	manifest, a vector of Packages
 * 				diff, the collision variable
 * Returns:		A trailer object
 */
Trailer pickNext(vector<Package> manifest, int diff) {
	Trailer trailer = Trailer();									// Create a trailer object for the simulation
	makeHeap(&manifest);											// Create a min heap using the manifest


	// Test to show the heap works properly
	while(manifest.size() > 0) {									// Iterate over the manifest
		vector <Package> collision;									// Create a vector for any collisions that take place

		collision.push_back(removeMin(&manifest));					// Take the top element of the heap

		while (manifest.size() > 0 && abs(manifest.front()			// Check if there is collision based off of the key
				.getFragility() - collision.front()
				.getFragility()) <= diff)
			collision.push_back(removeMin(&manifest));				// Add the package to the end of the list

		// If there is a collision
		if (collision.size() > 1) {
			compareSecondary(&collision, &trailer);					// Determine the next package to place in the truck

			for (int w = 1; w < (int)collision.size(); w++)			// Iterate over all the unused packages
				collision[w].getLocation().clear();					// Remove the locations of the unplaced packages

			manifest.insert(manifest.end(), collision.begin() + 1,	// Add the unplaced packages back to the manifest
					collision.end());
			makeHeap(&manifest);									// Generate the heap again
		} else {
			if ((collision).front().getIsPallet())												// Finding the location for a pallet
				(collision).front().setLocation(trailer.palletLocation((collision).front()));	// Find if the pallet fits
			else																				// Finding the location for a crate
				(collision).front().setLocation(trailer.crateLocation((collision).front()));	// Find if the crate fits

			if (collision.front().getLocation().size() == 0)		// If there is not a location
				continue;											// Move to the next package


		}
		if (collision.front().getLocation().size() != 0)			// Check if the location is found
			trailer.placePackage(collision.front());				// Place package in the truck
	}

	return trailer;													// Return the trailer with the packages placed
}
