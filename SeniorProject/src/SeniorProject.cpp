//============================================================================
// Name        : SeniorProject.cpp
// Author      : Chad Boyer (cboyer2016@my.fit.edu)
//				 William Ferrick (wferrick2016@my.fit.edu)
//				 Jordan Murray (jmurray2016@my.fit.edu)
//				 Connor Roth (croth2016@my.fit.edu)
// Description : Main Function to run the application
//============================================================================

// Include Packages
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Include header files
#include "PlacementAlgo.h"

// Use namespace std
using namespace std;

/*
 * Function: main
 * Description: Used to execute the placement algorithm
 * Parameters: argc, the number of command line arguments
 * 			   argv, command line values
 */
int main(int argc, char *argv[]) {

	if (argc == 0)	return 0;	// Check that there is a command line arguemnt passed

	ifstream file;				// Variable to read input
	file.open(argv[1]);			// Open the file

	string input;				// Used to read in input

	getline(file, input);		// Read in the column names

	vector<Package> manifest;	// Have a manifest of packages


	// Iterate over each word in the input
	while (getline(file, input, '\n')) {

		// Parse the input per line
		vector<int> packageInfo;
		// Iterate over string to find all
		for (int start = 0, end = 0; start < (int)input.length(); end++)
			if (input[end] == ',') {										// A comma is found
				packageInfo.push_back(stoi(input.substr(start, end)));		// Convert the string to an int and save
				start = end + 1;											// Move passed the comma
			}

		// Add the package object to a list of all package objects
		manifest.push_back(Package(packageInfo[0], packageInfo[1], packageInfo[2], packageInfo[3], packageInfo[4], packageInfo[5]));
	}

	// Run the placement algorithm on the manifest
	//for (int i = 0; i < 15; i++) {
	//	cout << i << endl;
		Trailer trailer = pickNext(manifest, 10);
		trailer.printTrailer();

	//}

}
