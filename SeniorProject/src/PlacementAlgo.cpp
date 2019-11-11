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

int Trailer::getWidth() {	return this->width;	}

/*
 * Function: 	Trailer
 * Description: Used to return how much of the trailer is filled
 * Parameters: 	none
 * Returns:		trailer attribute volume
 */
int Trailer::findVolume() {	return this->volume;	}

/*
 * Function: 	Trailer
 * Description: Used to construct a Trailer object
 * Parameters: 	none
 * Returns:		none
 */
Trailer::Trailer() {
	for (int i = 0; i < this->length; i++) {			// ITerate over the length of the truck
		for (int j = 0; j < this->width; j++) {			// Iterate over the width of the truck
			for (int k = 0; k < this->height; k++) {	// Iterate over the height of the truck
				weightedTrailer[i][j][k] = 0;			// Initialize each element to 0
			}
		}
	}
}

/*
 * Function: 	findLocation
 * Description: Used to find an open location for a package in the truck
 * Parameters: 	package, trying to be placed into the trailer
 * 				secondRun, shows if the length and width swapped
 * Returns:		location of the package in the trailer
 */
vector <int> Trailer::findLocation(Package package) {
	vector <int> location;															// Location where package should go

	// See if the package will fit
	//for (int height = 0; height < this->height; height++) {							// Iterate over the height of the trailer
	//	for (int length = 0; length < this->length; length++) {						// Iterate over the length of the trailer
			for (int width = 0; width < this->width; width++) {						// Iterate over the width of the trailer
				bool fits = true;
				// Check if there is a package that does not fit
				for (Package a : this->placedPackages) {
					cout << a.getID() << endl;
					vector <int> aLocation = a.getLocation();
					//for (int i = 0; i < a.getHeight() && fits; i++) {			// Iterate over the height of the package
					//	for (int j = 0; j < a.getLength() && fits; j++) {		// Iterate over the length of the package
					//		for (int k = 0; k < a.getWidth() && fits; k++) {	// Iterate over the width of the package
					//			if ((aLocation[2] == height && aLocation[1] == length && aLocation[0] == width)){
								if ((aLocation[2] == width) || ((aLocation[2] < width) && (aLocation[2] + a.getWidth() > width))
										|| ((aLocation[2] > width) && (aLocation[2] < width + package.getWidth()))) {
									fits = false;
									break;
								}
							//}
						//}
					//}
					//if (!fits)	break;
				}
				/*for (int i = 0; i < package.getHeight() && fits; i++) {			// Iterate over the height of the package
					for (int j = 0; j < package.getLength() && fits; j++) {		// Iterate over the length of the package
						for (int k = 0; k < package.getWidth() && fits; k++) {	// Iterate over the width of the package
							for (Package a : this->placedPackages) {
								vector <int> aLocation = a.getLocation();
								cout << a.getHeight() << ", " << a.getLength() << ", " << a.getWidth() << endl;
								if (aLocation[0] ) {
									cout << "Package " << a.getID() << " is already at this location: "<< height << " " << length << " " << width << endl;
 									fits = false;
									break;
								}
							}
						}
					}
				}*/
				// Now we know that the current level is free, loop over the rest of the index and see if it is free
				if (fits) {
					// Check if it fits the length, width, and height

					//cout << package.getID() << " Width: " << package.getWidth() << endl;
					//cout << width + package.getWidth() << endl;
					if (width + package.getWidth() <= this->width) {

					//location.push_back(height);									// Save the height first
					//location.push_back(length);									// Save the length second
						location.push_back(0);
						location.push_back(0);
						location.push_back(width);									// Save the width third
						return location;
					}
				}

			}
		//}
	//}
	/*for (int height = 0; height < this->height; height++) {							// Iterate over the height of the trailer
		for (int length = 0; length < this->length; length++) {						// Iterate over the length of the trailer
			for (int width = 0; width < this->width; width++) {						// Iterate over the width of the trailer
				if (simulation[height][length][width] == 0 &&						// Check if the location is empty
						(abs(height - this->height) >= package.getHeight()) &&		// Check if the package height fits
						(abs(width - this->width)   >= package.getWidth()) &&		// Check if the package width fits
						(abs(length - this->length) >= package.getLength())) {		// Check if the package length fits
					bool fits = true;												// Used to show if the package fits

					// Check if the package fits around the opening
					for (int i = 0; i < package.getHeight() && fits; i++) {			// Iterate over the height of the package
						for (int j = 0; j < package.getLength() && fits; j++) {		// Iterate over the length of the package
							for (int k = 0; k < package.getWidth() && fits; k++) {	// Iterate over the width of the package
								if (simulation[height+i][length+j][width+k] != 0) {	// Check if the spot is taken
									fits = false;									// Stops loops
								}
							}
						}
					}
					if (fits) {														// The package fits

						// Determine if the neighboring packages will break regulations (i.e.: Chemicals next to water), WILL'S REGULATIONS APPLY HERE
						// If Regulations say place is bad, then we claim package doesn't fit and try to find a new spot


						location.push_back(height);									// Save the height first
						location.push_back(length);									// Save the length second
						location.push_back(width);									// Save the width third
						return location;											// Return a vector of the x, y, & z position in the truck
					}
				}
			}
		}
	}*/
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
	for(int height = 0; height < package.getHeight(); height++) {			// Iterate over the length
		for(int length = 0; length < package.getLength(); length++) {		// Iterate over the width
			for(int width = 0; width < package.getWidth(); width++) {		// Iterate over the height
				this->weightedTrailer[(package.getLocation())[0] + height]	// Set the package ID in the trailer
						   [(package.getLocation())[1] + length]
						   [(package.getLocation())[2] + width]
							= package.getID();
			}
		}
	}
	this->volume -= package.findVolume();									// Deduct the volume of the package from the overall volume of the trailer
	this->placedPackages.push_back(package);								// Save the package as placed in the trailer
}

/*
 * Function: 	palletLocation
 * Description: Used to rotate the pallet correctly
 * Parameters: 	pallet, Package to be rotated
 * Returns:		none
 */
std::vector <int> Trailer::palletLocation(Package pallet) {
	vector <int> location = this->findLocation(pallet);		// Test the packages current dimensions for a spot (LWH)
	if (location.size() != 0) 	return location;			// The package fits, return the location
	pallet.swapLengthAndWidth();							// Rotate the Package's Length and Width (WLH)
	location = this->findLocation(pallet);					// Test the packages current dimensions for a spot
	return location;
}

std::vector <int> Trailer::crateLocation(Package crate) {
	vector <int> location = palletLocation(crate);			// Check if rotation like a pallet will work (LWH, WLH)
	if (location.size() != 0)	return location;			// The package fits, return the location

	crate.swapLengthAndWidth();								// Rotate the Package's Length and Width (WLH)
	crate.swapHeightAndWidth();								// Rotate the Package's Height and Width (WHL)
	location = this->findLocation(crate);					// Test the packages current dimensions for a spot
	if (location.size() != 0)	return location;			// The package fits, return the location
	crate.swapLengthAndWidth();								// Rotate the Package's Length and Width (HWL)
	location = this->findLocation(crate);					// Test the packages current dimensions for a spot
	if (location.size() != 0)	return location;			// The package fits, return the location
	crate.swapHeightAndWidth();								// Rotate the Package's Height and Width (HLW)
	location = this->findLocation(crate);					// Test the packages current dimensions for a spot
	if (location.size() != 0)	return location;			// The package fits, return the location
	crate.swapLengthAndWidth();								// Rotate the Package's Length and Width (LHW)
	location = this->findLocation(crate);					// Test the packages current dimensions for a spot

	return location;
}

/*
 * Function: 	printTrailer
 * Description: Used to print the 3D array of the trailer
 * Parameters:	none
 * Returns:		none
 */
void Trailer::printTrailer() {
	// Output the package ID at each spot
	cout << "Trailer Contents" << endl << "[H][L][W] = VALUE" << endl;
	/*for (int i = 0; i < this->getHeight(); i++)								// Iterate over the height
		for (int j = 0; j < this->getLength(); j++)							// Iterate over the length
			for (int k = 0; k < this->getWidth(); k++)						// Iterate over the width
				cout << "[" << i << "][" << j << "][" << k << "] = "		// Output to the location in the trailer
						<< this->weightedTrailer[i][j][k] << endl;*/
	for (Package a : this->placedPackages) {
		cout << a.getID() << ": ";
		cout << a.getLocation()[0] << ", " << a.getLocation()[1] << ", " << a.getLocation()[2] << endl;
		cout << "Height: " << a.getHeight() << " Length: " << a.getLength() << " Width: " << a.getWidth() << endl;
	}
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
		//if (collision)


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

			if (collision.front().getLocation().size() == 0) {		// If there is not a location
				continue;											// Move to the next package
			}
		}
		if (collision.front().getLocation().size() != 0) {			// Check if the location is found
			// Check and see if there is a better location for package

			//

			trailer.placePackage(collision.front());				// Place package in the truck
		}
		//cout << "Placed the package: " << collision.front().getID() << endl;
	}
	return trailer;													// Return the trailer with the packages placed
}
