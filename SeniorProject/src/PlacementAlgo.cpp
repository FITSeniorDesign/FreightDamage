//============================================================================
// Name        : PlacementAlgo.cpp
// Author      : Chad Boyer (cboyer2016@my.fit.edu)
//				 William Ferrick (wferrick2016@my.fit.edu)
//				 Jordan Murray (jmurray2016@my.fit.edu)
//				 Connor Roth (croth2016@my.fit.edu)
// Description : Source file to place Packages into a Trailer
//============================================================================


#include <iostream>
#include <fstream>
#include <string>
#include "PlacementAlgo.h"

using namespace std;

// Package getter functions for each attribute
int Package::getFragility() {
	return this->fragility;
}

int Package::getHeight() {
	return this->height;
}

int Package::getLength() {
	return this->length;
}

int Package::getID() {
	return this->iD;
}

int Package::getWeight() {
	return this->weight;
}

int Package::getWidth() {
	return this->width;
}

std::string Package::getDescription() {
	return this->description;
}

// Package setter functions for each attribute
void Package::setFragility(int fragility) {
	this->fragility = fragility;
}

void Package::setHeight(int height) {
	this->height = height;
}

void Package::setLength(int length) {
	this->length = length;
}

void Package::setID(int iD) {
	this->iD = iD;
}

void Package::setWeight(int weight) {
	this->weight = weight;
}

void Package::setWidth(int width) {
	this->width = width;
}

void Package::setDescription(std::string description) {
	this->description = description;
}

int Package::findVolume() {
	return length * width * height;
}

/*
 * Function: Package
 * Description: Used to construct a Package object
 * Parameters: iD, the ID of the package
 *             weight, the weight of the package
 *             length, the length of the package
 *             width, the width of the package
 *             height, the height of the package
 *             fragility, the fragility of the package
 */
Package::Package(int iD, int weight, int length, int width, int height, int fragility) {
	// Call setter functions on each variable
	setID(iD);
	setWeight(weight);
	setLength(length);
	setWidth(width);
	setHeight(height);
	setFragility(fragility);
}



// Trailer getter functions for each attribute
int Trailer::getHeight() {
	return this->height;
}

int Trailer::getLength() {
	return this->length;
}

int Trailer::getWidth() {
	return this->width;
}


Trailer::Trailer() {
	for (int i = 0; i < this->length; i++) {
		for (int j = 0; j < this->width; j++) {
			for (int k = 0; k < this->height; k++) {
				simulation[i][j][k] = 0;
			}
		}
	}
}

int* Trailer::findLocation(Package package) {
	int locLen = 0, locWid = 0, locHei = 0, *ptr;
	bool fitsHeight = false, fitsWidth = false, fitsLength = false;
	//for (int length = locLen; length < this->length; length++) {
		for (int width = locWid; width < this->width; width++) {
			for (int height = locHei; height < this->height; height++) {
				if (simulation[length][width][height] == 0) {
					locHei = height;
					int i = 0;
					for (; i < package.getHeight(); i++) {
						if (simulation[length][width][height+i] != 0) {
							fitsHeight = false;
							break;
						}
					}
					if (!fitsHeight) {
						height += i;
						fitsHeight = true;
					} else	break;
					cout << "doesn't fit, move over" << endl;
				}
			}
			cout << "height starts at: " << locHei << endl;
		}
		if (abs(width - locWid) >= package.getWidth()) {
			cout << "I am here" << endl;
		}
	//}
	return ptr;
}

int Trailer::findVolume() {
	return this->volume;
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
		bool firstFits = false, secondFits = false;

		char compare = 0;

		// Check if the volumes of both fit in the truck
		if ((*trailer).findVolume() > (*collision)[0].findVolume()) {
			//int *ptr = 0;
			//if (ptr != nullptr)
			//	firstFits = true;
			//else
			//	compare++;					// Swap out the first one with the second one
		}

		if ((*trailer).findVolume() > (*collision)[i].findVolume()) {
			int *ptr = 0;
			if (ptr != nullptr)
				secondFits = true;
		}

		if (firstFits & secondFits) {
			// Check the weight of the packages
			compare = compareWeight((*collision)[0], (*collision)[i]);

		}

		// If the second package should be placed first
		if (compare > 0) {
			// Swap the two packages
			Package temp = (*collision)[0];
			(*collision)[0] = (*collision)[i];
			(*collision)[i] = temp;
		}
	}
}

/*
 * Function: placement
 * Description: Used to construct the min heap using a vector
 * Parameters: manifest, a vector of Packages
 */
void placement(vector<Package> manifest) {
	// Construct a heap using a vector
	Trailer trailer = Trailer();

	//cout << trailer.findVolume() << endl;
	//trailer.constructSimulation();

	makeHeap(&manifest);										// Create a min heap using the vector

	vector <Package> collision;
	int diff = 10;

	// Test to show the heap works properly
	while(manifest.size() > 0) {
		collision.push_back(removeMin(&manifest));

		while (manifest.size() > 0 && abs(manifest.front().getFragility() - collision.front().getFragility()) <= diff)
			collision.push_back(removeMin(&manifest));

		// If there is a collision
		if (collision.size() > 1) {

			// Determine which pacakges fit in the truck
			compareSecondary(&collision, &trailer);

			// Add the rest of the list back to the manifest and make it a heap again
			manifest.insert(manifest.end(), collision.begin() + 1, collision.end());
			makeHeap(&manifest);
		}

		cout << collision.front().getFragility() << endl;
		collision.clear();
		//cout << removeMin(&manifest).getFragility() << endl;
	}

}
