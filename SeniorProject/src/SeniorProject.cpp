//============================================================================
// Name        : SeniorProject.cpp
// Author      : Chad Boyer (cboyer2016@my.fit.edu)
//				 William Ferrick (wferrick2016@my.fit.edu)
//				 Jordan Murray (jmurray2016@my.fit.edu)
//				 Connor Roth (croth2016@my.fit.edu)
// Description : Main Function to run the application
//============================================================================

// Include Packages
#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <QApplication>

// Include header files
#include "PlacementAlgo.h"

// Declare used namespace
using namespace std;

/*
 * Function: 	main
 * Description: Used to execute the placement algorithm
 * Parameters:	argc, the number of command line arguments
 * 				argv, command line values
 * Returns:		0 means no errors
 * 				1 means errors occurred
 */
int main(int argc, char *argv[]) {

	if (argc == 0)	return 1;												// Check that there is a command line argument passed

	ifstream file;															// Variable to read input
	file.open(argv[1]);														// Open the file

	string input;															// Used to read in input
	getline(file, input);													// Read in the column names

	vector<Package> manifest;												// Have a manifest of packages

	while (getline(file, input, '\n')) {									// Iterate over each line in the input
		vector<int> packageInfo;											// Vector to hold the package information
		for (int start = 0, end = 0; start < (int)input.length(); end++)	// Iterate over the entire string
			if (input[end] == ',') {										// A comma is found
				try {														// Try a statement
					packageInfo.push_back(stoi(input.substr(start, end)));	// Convert the string to an int and save
				} catch (...) {												// Catch any exception thrown
					if (input.substr(start, end) == "Yes")					// Input was yes
						packageInfo.push_back(1);							// Push on a true
					else													// Input was not yes
						packageInfo.push_back(0);							// Push on a false
				}
				start = end + 1;											// Move passed the comma
			}

		manifest.push_back(Package(packageInfo[0], packageInfo[1],			// Add the package object to a list of all package objects
				packageInfo[2], packageInfo[3], packageInfo[4],
				packageInfo[5], packageInfo[6]));
	}


	// Export to a text file
	bool exportTextFile = false;														// Check if the user wants to export the text file
	if (exportTextFile) {															// The user wants a text file
		string textFile = "Output.txt";												// Text file name for the output
		freopen(textFile.c_str(), "w", stdout);										// Console output to the text file

		// Run function pickNext to decide what to place next
		for (int i = 10; i < 11; i++) {												// Check over multiple different options
			Trailer trailer = pickNext(manifest, i);								// Return the trailer of all the items placed
			cout << "Trailer Remaining Volume: " << trailer.findVolume() << endl;	// List the volume consumed in the trailer
			trailer.printTrailer();													// Test, do not include in final product
		}

	} else	{																		// The user does not want a text file
		// Run function pickNext to decide what to place next
		Trailer best;
		for (int i = 0; i < 15; i++) {												// Check over multiple different options
			Trailer other = pickNext(manifest, i);								// Return the trailer of all the items placed
			if (best.findVolume() > other.findVolume())
				best = other;
		}
		cout << "Trailer Remaining Volume: " << best.findVolume() << endl;	// List the volume consumed in the trailer
		best.printTrailer();													// Test, do not include in final product

	}
	// Determine which one should be used based off of testing the package damage in each as well as the best filled option



    //Implementation of GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


}
