//============================================================================
// Name        : SeniorProject.cpp
// Author      : Chad Boyer
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "PlacementAlgo.h"
using namespace std;

int main(int argc, char *argv[]) {
	string word;
	ifstream file;
	if (argc == 0)
		return 0;
	file.open(argv[1]);		// Open the file

	string input;			// Used to read in input

	getline(file, input);		// Read in the column names

	vector<Package> manifest;	// Have a manifest of packages


	while (getline(file, input, '\n')) {
		// Take the information from the input fields
		vector<int> vect;
		std::stringstream ss(input);
		for (int i; ss >> i;) {
			vect.push_back(i);
		    if (ss.peek() == ',')
		        ss.ignore();
		}

		// Store the values in a package object
		Package a = Package(vect[0], vect[1], vect[2], vect[3], vect[4], vect[5]);
		// Add the object to the list
		manifest.push_back(a);
	}

	// Run the placement algorithm on the manifest
	placement(manifest);

}
