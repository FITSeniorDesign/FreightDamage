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

// Trailer setter functions for each attribute
void Trailer::setHeight(int height) {
	this->height = height;
}

void Trailer::setLength(int length) {
	this->length = length;
}

void Trailer::setWidth(int width) {
	this->width = width;
}

/*
 * Function: Trailer
 * Description: Used to construct a Trailer object
 * Parameters: length, length of the trailer
 * 			   width, width of the trailer
 * 			   height, height of the trailer
 */
Trailer::Trailer(int lenth, int width, int height) {
	setLength(length);
	setWidth(width);
	setHeight(height);
}

/*
 * Function: constructSimulation
 * Description: Used to construct a 3D Trailer
 * Parameters: none
 */
void Trailer::constructSimulation () {
	int simulation[length][width][height];
	for (int l = 0; l < length; l++) {
		cout << simulation[l][0][0]<< endl;
	}

}



/*
 * Function: heapify
 * Description: Used to sort the max heap based off of the key
 * Parameters: heap, a pointer to a vector of Packages
 *             index, location of where to sort the heap.
 */
void heapify (vector<Package> *heap, int index) {
	int largest = index;								// Find the parent
	int left = 2 * index + 1;							// Find the left child
	int right = 2 * index + 2;							// Find the right child

	// Check if the left child is greater than the parent based off key
	if (left < (int)heap->size() && (*heap)[left].getFragility() > (*heap)[largest].getFragility())
		largest = left;

	// Check if the right child is greater than the parent based off key
	if (right < (int)heap->size() && (*heap)[right].getFragility() > (*heap)[largest].getFragility())
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
 * Function: peekHeap
 * Description: Used to return the top key from the max heap item without removing it
 * Parameters: heap, a pointer to a vector of Packages
 */
Package peekHeap(vector <Package> *heap) {
	return (*heap)[0];									// Return the value of the top element in the list
}

/*
 * Function: removeMax
 * Description: Used to remove the top key from the max heap
 * Parameters: heap, a pointer to a vector of Packages
 */
Package removeMax(vector <Package> *heap) {
	Package popped = (*heap)[0];						// Save the top element
	(*heap)[0] = (*heap)[(*heap).size() - 1];			// Move the last element to the top
	(*heap).pop_back();									// Remove the last element from the heap
	heapify(heap, 0);									// Heapify the entire heap
	return popped;										// Return the removed element
}

/*
 * Function: makeHeap
 * Description: Used to construct the max heap using a vector
 * Parameters: heap, a pointer to a vector of Packages
 */
void makeHeap(vector<Package> *heap) {
	int lastNonLeaf = (heap->size()/2) - 1;				// Find the last location of a non-leaf in the vector

	for (int i = lastNonLeaf; i >= 0; i--)				// Iterate over all non-leaves
		heapify (heap, i);								// Create a max heap on the non-leaves
}

/*
 * Function: placement
 * Description: Used to construct the max heap using a vector
 * Parameters: manifest, a vector of Packages
 */
void placement(vector<Package> manifest) {
	// Construct a heap using a vector
	Trailer trailer = Trailer(53*2, 8.5*2, 13*2);

	trailer.constructSimulation();

	makeHeap(&manifest);										// Create a max heap using the vector

	// Test to show the heap works properly
	while(manifest.size() > 0)
		cout << removeMax(&manifest).getFragility() << endl;

}
