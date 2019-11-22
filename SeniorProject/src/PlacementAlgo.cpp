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
	for (int i = 0; i < this->length; i++)				// Iterate over the length of the truck
		for (int j = 0; j < this->width; j++)			// Iterate over the width of the truck
			for (int k = 0; k < this->height; k++)		// Iterate over the height of the truck
				weightedTrailer[i][j][k] = 0;			// Initialize each element to 0
}

/*
 * Function: 	findLocation
 * Description: Used to find an open location for a package in the truck
 * 				based off the location of other packages.
 * Parameters: 	package, trying to be placed into the trailer
 * Returns:		location of the package in the trailer
 */
vector <int> Trailer::findLocation(Package package) {
	vector <int> location;															// Location where package should go

	// See if the package will fit
	for (int height = 0; height < this->height - package.getHeight(); height++) {								// Iterate over the height of the trailer
		for (int length = 0; length < this->length - package.getLength(); length++) {	// Iterate over the length of the trailer
			for (int width = 0; width < this->width - package.getWidth(); width++) {	// Iterate over the width of the trailer
				bool fits = true;														// Boolean to show there is a fill or not
				// Check if the package fits around the other packages
				for (Package a : this->placedPackages) {								// Iterate over all placed packages
					vector <int> aLocation = a.getLocation();							// Get the location of the current package
					if ((aLocation[2] == width && aLocation[1] == length &&				// The current location is filled
							aLocation[0] == height)) {
						fits = false;													// The package does not fit here
						break;															// Break out of the loop and
					}
				}

				// Check if the package fits
				for (int i = 0; i < this->height && fits; i++)							// Iterate over the packages height
					for (int j = 0; j < this->length && fits; j++)						// Iterate over the packages length
						for(int k = 0; k < this->width && fits; k++)					// Iterate over the packages width
							for (Package a : this->placedPackages) {					// Iterate over the currently placed packages
								vector <int> aLocation = a.getLocation();				// Get the location of the current package
								if ((aLocation[0] == height+i) || ((aLocation[0] < height+i)		// Check if the height is taken or the package ranges into the location
										&& (aLocation[0] + a.getHeight() > height+i)))
									if ((aLocation[1] == length+j) || ((aLocation[1] < length+j)	// Check if the length is taken or the package ranges into the location
											&& (aLocation[1] + a.getLength() > length+j)))
										if ((aLocation[2] == width+k) || ((aLocation[2] < width+k)	// Check if the width is taken or the package ranges into the location
												&& (aLocation[2] + a.getWidth() > width+k))) {
											fits = false;											// The package doesn't fit
											break;													// Break out of the placed packages loop
										}
							}
				if (fits) {
					location.push_back(height);								// Save the height first
					location.push_back(length);								// Save the length second
					location.push_back(width);								// Save the width third
					return location;
				}
			}
		}
	}

	return location;																// Return the location found and empty if no spot
}

/*
 * Function: 	placePackage
 * Description: Used to put the package in the truck at the location
 * Parameters: 	package, placed into the trailer
 * Returns:		none
 */
void Trailer::placePackage(Package package) {
	// Place a package in the weighted trailer
	for(int height = 0; height < package.getHeight(); height++)				// Iterate over the length
		for(int length = 0; length < package.getLength(); length++)			// Iterate over the width
			for(int width = 0; width < package.getWidth(); width++)			// Iterate over the height
				this->weightedTrailer[(package.getLocation())[0] + height]	// Set the package ID in the trailer
						   [(package.getLocation())[1] + length]
						   [(package.getLocation())[2] + width]
							= package.getID();

	this->volume -= package.findVolume();									// Deduct the volume of the package from the overall volume of the trailer
	this->placedPackages.push_back(package);								// Save the package as placed in the trailer
}

/*
 * Function: 	furthestBack
 * Description: Used to determine the better location in the truck
 * Parameters: 	package, placed into the trailer
 * 				a, first location in the trailer
 * 				b, second location in the trailer
 * Returns:		none
 */
std::vector<int> Trailer::furthestBack(Package dimensionsA, Package dimensionsB, std::vector<int> a, std::vector<int> b) {
	char compare = 0;							// Used to determine which location to use

	/*if (a[0] == b[0]) {			// The same layer is being examined
		if (a[1] < b[1] && a[2] < b[2])			compare++;		// Vector a's length is farther back
		else if (a[1] < b[1] && a[2] == b[2])	compare--;						// Vector b's length is farther back
		//else if (a[1] < b[1] && a[2] > b[2])	compare = compare;						// Vector a's width is farther back
		else if (a[1] > b[1] && a[2] > b[2])	compare++;						// Vector b's width is farther back
		else if (a[1] > b[1] && a[2] == b[2])	compare++;
		else if (a[1] == b[1] && a[2] > b[2])	compare++;
		else if (a[1] == b[1] && a[2] < b[2])	compare--;
	} else if (a[0] < b[0])		compare++;
	else						compare--;*/
	//else				compare--;				// Vector b's height is farther down
	//if (a[1] < b[1]) 	compare++;				// Vector a's length is farther back
	//else				compare--;				// Vector b's length is farther back
	//if (a[2] < b[2])	compare++;				// Vector a's width is farther back
	//else				compare--;				// Vector b's width is farther back


	if (a[0] == b[0] && a[1] > b[1])		compare++;
	else if (a[0] == b[0] && a[1] < b[1])	compare--;
	else if (a[0] < b[0]) 					compare++;
	else 									compare--;

	// Check if placement a touches two walls
	/*if (((a[2] == 0 || a[2] + dimensionsA.getWidth() == this->width) && (a[1] == 0 || a[1] + dimensionsA.getLength() == this->length))		// Check width and length
		|| ((a[2] == 0 || (a[2] + dimensionsA.getWidth() == this->width)) && (a[0] == 0 || (a[0] + dimensionsA.getHeight() == this->height)))		// Check width and height
		|| ((a[0] == 0 || (a[0] + dimensionsA.getHeight() == this->height)) && (a[1] == 0 || (a[1] + dimensionsA.getLength() == this->length))))	// Check height and length
			compare++;

	// Check if placement b touches two walls
	if (((b[2] == 0 || (b[2] + dimensionsB.getWidth() == this->width)) && (b[1] == 0 || (b[1] + dimensionsB.getLength() == this->length)))		// Check width and length
		|| ((b[2] == 0 || (b[2] + dimensionsB.getWidth() == this->width)) && (b[0] == 0 || (b[0] + dimensionsB.getHeight() == this->height)))		// Check width and height
		|| ((b[0] == 0 || (b[0] + dimensionsB.getHeight() == this->height)) && (b[1] == 0 || (b[1] + dimensionsB.getLength() == this->length))))	// Check height and length
			compare--;*/

	// Determine which one to use
	if (compare <= 0)		// The second is more beneficial
		return b;			// Return the second placement
	return a;				// Return the first placement
}


/*
 * Function: 	palletLocation
 * Description: Used to rotate the pallet correctly
 * Parameters: 	pallet, Package to be rotated
 * Returns:		none
 */
std::vector <int> Trailer::palletLocation(Package &pallet) {
	vector <int> locationA = this->findLocation(pallet);		// Test the packages current dimensions for a spot (LWH)
	Package dimensionA = pallet;								// Used for the first dimension of the pallet

	pallet.swapLengthAndWidth();								// Rotate the Package's Length and Width (WLH)
	vector <int> locationB = this->findLocation(pallet);		// Test the packages current dimensions for a spot
	if (locationA.size() == 0) {								// If there is not a location found before
		locationA = locationB;									// Save the location in the first spot
		dimensionA = pallet;									// Move the dimensions into dimensionA
	} else if (locationB.size() != 0 && locationA.size() != 0)		// There are two locations to check
		if (this->furthestBack(dimensionA, pallet, locationA, locationB) == locationB) {	// Check which is the better placement
			dimensionA = pallet;								// Save the new pallet dimensions
			locationA = locationB;									// Save the better
		}

	pallet = dimensionA;											// Update the pallet before returning it

	return locationA;												// Return the furthest back location
}

/*
 * Function: 	crateLocation
 * Description: Used to rotate the crate correctly
 * Parameters: 	crate, Package to be rotated
 * Returns:		none
 */
std::vector <int> Trailer::crateLocation(Package &crate) {
	Package dimensionA = crate;									// Save the original dimensions of the pacakge
	vector <int> locationA = palletLocation(crate);				// Check if rotation like a pallet will work (LWH, WLH)
	if (dimensionA.getHeight() == crate.getHeight()		// Check if the dimensions changed or not
			&& dimensionA.getLength() == crate.getLength()
			&& dimensionA.getWidth() == crate.getWidth())
		crate.swapLengthAndWidth();								// Rotate the Package's Length and Width (WLH)


	crate.swapHeightAndWidth();								// Rotate the Package's Height and Width (WHL)
	vector <int> locationB = this->findLocation(crate);		// Test the packages current dimensions for a spot
	if (locationA.size() == 0) {								// If there is not a location found before
		locationA = locationB;									// Save the location in the first spot
		dimensionA = crate;									// Move the dimensions into dimensionA
	} else if (locationB.size() != 0 && locationA.size() != 0)	//
		if (this->furthestBack(dimensionA, crate, locationA, locationB) == locationB) {									//
			dimensionA = crate;								// Save the new pallet dimensions
			locationA = locationB;									// Save the better
		}


	crate.swapLengthAndWidth();								// Rotate the Package's Length and Width (HWL)
	locationB = this->findLocation(crate);		// Test the packages current dimensions for a spot
	if (locationA.size() == 0) {								// If there is not a location found before
		locationA = locationB;									// Save the location in the first spot
		dimensionA = crate;									// Move the dimensions into dimensionA
	} else if (locationB.size() != 0 && locationA.size() != 0)	//
		if (this->furthestBack(dimensionA, crate, locationA, locationB) == locationB) {									//
			dimensionA = crate;								// Save the new pallet dimensions
			locationA = locationB;									// Save the better
		}

	crate.swapHeightAndWidth();								// Rotate the Package's Height and Width (HLW)
	locationB = this->findLocation(crate);		// Test the packages current dimensions for a spot
	if (locationA.size() == 0) {								// If there is not a location found before
		locationA = locationB;									// Save the location in the first spot
		dimensionA = crate;									// Move the dimensions into dimensionA
	} else if (locationB.size() != 0 && locationA.size() != 0)	//
		if (this->furthestBack(dimensionA, crate, locationA, locationB) == locationB) {									//
			dimensionA = crate;								// Save the new crate dimensions
			locationA = locationB;									// Save the better
		}

	crate.swapLengthAndWidth();								// Rotate the Package's Length and Width (LHW)
	locationB = this->findLocation(crate);		// Test the packages current dimensions for a spot
		if (locationA.size() == 0) {								// If there is not a location found before
			locationA = locationB;									// Save the location in the first spot
			dimensionA = crate;									// Move the dimensions into dimensionA
		} else if (locationB.size() != 0 && locationA.size() != 0)	//
			if (this->furthestBack(dimensionA, crate, locationA, locationB) == locationB) {									//
				dimensionA = crate;								// Save the new crate dimensions
				locationA = locationB;									// Save the better
			}

	crate = dimensionA;
	return locationA;
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
	if (a.getWeight() > b.getWeight())			// Package 1 weighs more than Package 2
		return -1;								// Shows the packafe a has precedence
	else if (a.getWeight() < b.getWeight())		// Package 2 weighs more than Package 1
		return 1;								// Returns package b has precedence
	else
		return 0;									// Package weight are equal, don't influence the final total
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
		if (collision.front().getLocation().size() != 0) {			// Check if the location is found

			// Check and see if there is a better location for package

			//

			trailer.placePackage(collision.front());				// Place package in the truck
		}
	}
	return trailer;													// Return the trailer with the packages placed
}
