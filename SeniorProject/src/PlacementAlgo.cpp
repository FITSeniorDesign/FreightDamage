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

using namespace std;

// Package getter functions for each attribute
int Package::getFragility() {	return this->fragility;	}

int Package::getHeight() {	return this->height;	}

int Package::getLength() {	return this->length;	}

int Package::getID() {	return this->iD;	}

int Package::getWeight() {	return this->weight;	}

int Package::getWidth() {	return this->width;	}

vector<int> Package::getLocation() {	return location;	}

// Package setter functions for each attribute
void Package::setFragility(int fragility) {	this->fragility = fragility;	}

void Package::setHeight(int height) {	this->height = height;	}

void Package::setLength(int length) {	this->length = length;	}

void Package::setID(int iD) {	this->iD = iD;	}

void Package::setWeight(int weight) {	this->weight = weight;	}

void Package::setWidth(int width) {	this->width = width;	}

void Package::setLocation(vector<int> location) {	this->location = location;	}

/*
 * Function: 	findVolume
 * Description: Used to return the volume of the package
 * Parameters: 	none
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
 */
Package::Package(int iD, int weight, int length, int width, int height, int fragility) {
	// Call setter functions called on each attribute
	setID(iD);					// Set the ID of the package
	setWeight(weight);			// Set the Weight of the package
	setLength(length);			// Set the Length of the package
	setWidth(width);			// Set the Width of the package
	setHeight(height);			// Set the Height of the apckage
	setFragility(fragility);	// Set the fragility of the package
}



// Trailer getter functions for each attribute
int Trailer::getHeight() {	return this->height;	}

int Trailer::getLength() {	return this->length;	}

int Trailer::getWidth() {	return this->width;	}

/*
 * Function: 	Trailer
 * Description: Used to construct a Trailer object
 * Parameters: 	none
 */
int Trailer::findVolume() {	return this->volume;	}

/*
 * Function: 	Trailer
 * Description: Used to construct a Trailer object
 * Parameters: 	none
 */
Trailer::Trailer() {
	for (int i = 0; i < this->length; i++) {			// ITerate over the length of the truck
		for (int j = 0; j < this->width; j++) {			// Iterate over the width of the truck
			for (int k = 0; k < this->height; k++) {	// Iterate over the height of the truck
				simulation[i][j][k] = 0;				// Initialize each element to 0
			}
		}
	}
}

vector <int> Trailer::findLocation(Package package) {
	//cout << "findLocation" << endl;
	vector <int> location;
	for (int length = 0; length < this->length; length++) {
		for (int width = 0; width < this->width; width++) {
			for (int height = 0; height < this->height; height++) {
				if (simulation[length][width][height] == 0 &&
						(abs(height - this->height) >= package.getHeight()) &&
						(abs(width - this->width)   >= package.getWidth()) &&
						(abs(length - this->length) >= package.getLength())) {
					bool fits = true;
					//cout << package.getLength() << endl << package.getWidth() << endl << package.getHeight() << endl ;
					for (int i = 0; i < package.getLength() && fits; i++) {
						for (int j = 0; j < package.getWidth() && fits; j++) {
							for (int k = 0; k < package.getHeight() && fits; k++) {
								//cout << "length: " << length + i << " width: " << width + j << " height: " << height + k << endl;
								//if (length+i == 0 && width+j == 1 && height+k == 0) {
								//	cout << simulation[length+i][width+j][height+k];
								//}
								if (simulation[length+i][width+j][height+k] != 0) {
									cout << "there is a package here" << endl;
									length += i;
									width += j;
									height += k;
									fits = false;
								}
							}
						}
					}
					if (fits) {
						//cout << "fits" << endl;
						location.push_back(length);
						location.push_back(width);
						location.push_back(height);
						// Return a vector of the three positions
						return location;//&simulation[length][width][height];
					}
				}
			}
		}
	}

	return location;
}


void Trailer::placePackage(Package package) {
	for(int length = 0; length < package.getLength(); length++) {
		for(int width = 0; width < package.getWidth(); width++) {
			for(int height = 0; height < package.getHeight(); height++) {
				simulation[(package.getLocation())[0] + length][(package.getLocation())[1] + width][(package.getLocation())[2] + height] = package.getID();
			}
		}
	}
	this->volume -= package.findVolume();		// Deduct the volume of the package from the overall volume of the trailer
}

void Trailer::printTrailer() {
	// Output the package ID at each spot
	for (int i = 0; i < this->getLength(); i++) {
		for (int j = 0; j < this->getWidth(); j++) {
			for (int k = 0; k < this->getHeight(); k++) {
				cout << "[" << i << "][" << j << "][" << k << "] = " << this->simulation[i][j][k] << endl;
				//simulation[i][j][k] = 0;
			}
		}
	}
}



/*
 * Function: heapify
 * Description: Used to sort the min heap based off of the key
 * Parameters: heap, a pointer to a vector of Packages
 *             index, location of where to sort the heap.
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
 * Function: removemin
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

int compareWeight(Package a, Package b) {
	if (a.getWeight() > b.getWeight()) {
		return -1;
	} else if (a.getWeight() < b.getWeight()) {
		return 1;
	}
	return 0;
}

void compareSecondary (vector <Package> *collision, Trailer *trailer){
	for (int i = 1; i < (int)(*collision).size(); i++) {
		cout << "comparing: " << (*collision)[0].getFragility() << " with: " << (*collision)[i].getFragility() << endl;

		char compare = 0;

		// Check if the volumes of both fit in the truck
		if ((*trailer).findVolume() > (*collision)[0].findVolume()) {
			(*collision).front().setLocation(trailer->findLocation((*collision).front()));	// Find if it actually fits
			if ((*collision).front().getLocation().size() == 0)	compare ++;		// The location is not found
			else 											compare --;		// The location is found
		}

		if ((*trailer).findVolume() > (*collision)[i].findVolume()) {
			(*collision)[i].setLocation(trailer->findLocation((*collision)[i]));	// Find if it actually fits
			if (compare == 1 && (*collision)[i].getLocation().size() == 0) continue;	// Neither package fits, skip
			else if ((*collision)[i].getLocation().size() == 0)	compare ++;			// The location is not found
			else if ((*collision)[i].getLocation().size() != 0)	compare --;			// The location is found

		}

		// Both packages fit
		if (compare == 0) {
			// Check the weight of the packages
			cout << "checking: " << (*collision).front().getWeight() << " vs: " << (*collision)[i].getWeight() << endl;
			compare += compareWeight((*collision).front(), (*collision)[i]);

		}

		// If the two packages are equal, keep the one with the lower fragility
		if (compare == 0)	continue;
		else if (compare > 0) {						// The second package should be placed first
			// Swap the two packages
			Package temp = (*collision).front();
			(*collision).front() = (*collision)[i];
			(*collision)[i] = temp;
		}

	}
}

/*
 * Function: pickNext
 * Description: Used to construct the min heap using a vector
 * Parameters: manifest, a vector of Packages
 */
Trailer pickNext(vector<Package> manifest, int diff) {
	// Construct a heap using a vector
	Trailer trailer = Trailer();
	makeHeap(&manifest);										// Create a min heap using the vector

	// Test to show the heap works properly
	while(manifest.size() > 0) {
		vector <Package> collision;

		for (int w = 0; w < (int)manifest.size(); w++)
			cout << (manifest)[w].getFragility() << ", ";
		cout << endl;

		collision.push_back(removeMin(&manifest));

		// Check if there is collision based off of the key
		while (manifest.size() > 0 && abs(manifest.front().getFragility() - collision.front().getFragility()) <= diff)
			collision.push_back(removeMin(&manifest));

		// If there is a collision
		if (collision.size() > 1) {

			// Determine the next package to place
			compareSecondary(&collision, &trailer);

			// Set all of the other locations to nullptr
			for (int w = 1; w < (int)collision.size(); w++) {
				collision[w].getLocation().clear();
			}
			// Add the rest of the list back to the manifest and make it a heap again
			manifest.insert(manifest.end(), collision.begin() + 1, collision.end());
			makeHeap(&manifest);
		} else {								// Check if the other package can be placed
			collision.front().setLocation(trailer.findLocation(collision.front()));
			if (collision.front().getLocation().size() == 0)	continue;
		}
		trailer.placePackage(collision.front());						// Place package in the truck
	}
	return trailer;
}
