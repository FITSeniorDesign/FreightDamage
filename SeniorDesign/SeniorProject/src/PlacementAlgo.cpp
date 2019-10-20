/*
 * PlacementAlgo.cpp
 *
 *  Created on: Oct 19, 2019
 *      Author: elcha
 */


#include <iostream>
#include <fstream>
#include <string>
#include "PlacementAlgo.h"

using namespace std;

void placement () {
	return;
}

int Package::getFragility() {
	return this->fragility;
}

int Package::getHeight() {
	return this->height;
}

int Package::getLength() {
	return this->length;
}

int Package::getPackageNumber() {
	return this->packageNumber;
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

void Package::setFragility(int fragility) {
	this->fragility = fragility;
}

void Package::setHeight(int height) {
	this->height = height;
}

void Package::setLength(int length) {
	this->length = length;
}

void Package::setPackageNumber(int packageNumber) {
	this->packageNumber = packageNumber;
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

Package::Package(int packageNumber, int weight, int length, int width, int height, int fragility) {
	setPackageNumber(packageNumber);
	setWeight(weight);
	setLength(length);
	setWidth(width);
	setHeight(height);
	setFragility(fragility);
}

void placement(std::vector<Package> manifest) {
	for(int i = 0; i < (int)manifest.size(); i++) {
		cout << manifest[i].getPackageNumber() << endl;
	}
}
