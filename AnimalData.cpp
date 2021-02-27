/*
 * AnimalData.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: 1903558_snhu
 */

#include "AnimalData.h"

// Default constructor
AnimalData::AnimalData() {
	trackNum = "-1";
	name = "";
	type = "";
	subtype = "";
	eggs = -1;
	nurse = -1;
}

// Explicit constructor
AnimalData::AnimalData(string inTrackNum, string inName, string inType, string inSubType, int inEggs, int inNurse) {
	trackNum = inTrackNum;
	name = inName;
	type = inType;
	subtype = inSubType;
	eggs = inEggs;
	nurse = inNurse;
}

// Destructor
AnimalData::~AnimalData() {
	// TODO Auto-generated destructor stub
}

// Accessors
string AnimalData::getTrackNum() {
	return trackNum;
}

string AnimalData::getName() {
	return name;
}

string AnimalData::getType() {
	return type;
}

string AnimalData::getSubType() {
	return subtype;
}

int AnimalData::getEggs() {
	return eggs;
}

int AnimalData::getNurse() {
	return nurse;
}

// Mutators
void AnimalData::setTrackNum(string inTrackNum) {
	trackNum = inTrackNum;
}

void AnimalData::setName(string inName) {
	name = inName;
}

void AnimalData::setType(string inType) {
	type = inType;
}

void AnimalData::setSubType(string inSubType) {
	subtype = inSubType;
}

void AnimalData::setEggs(int inEggs) {
	eggs = inEggs;
}

void AnimalData::setNurse(int inNurse){
	nurse = inNurse;
}

// Print function for use with displaying object data
void AnimalData::print() {
	cout << trackNum << " | ";
	cout << name << " | ";
	cout << type << " | ";
	cout << subtype << " | ";
	cout << eggs << " | ";
	cout << nurse << endl;
}
