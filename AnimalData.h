/*
 * AnimalData.h
 *
 *  Created on: Feb 21, 2021
 *      Author: 1903558_snhu
 */

#ifndef ANIMALDATA_H_
#define ANIMALDATA_H_
#include <iostream>
using namespace std;

class AnimalData {
public:
	AnimalData();
	AnimalData(string inTrackNum, string inName, string inType, string inSubType, int inEggs, int inNurse);
	virtual ~AnimalData();
	string getTrackNum();
	string getName();
	string getType();
	string getSubType();
	int getEggs();
	int getNurse();
	void setTrackNum(string inTrackNum);
	void setName(string inName);
	void setType(string inType);
	void setSubType(string inSubType);
	void setEggs(int inEggs);
	void setNurse(int inNurse);
	void print();
private:
	string trackNum;
	string name;
	string type;
	string subtype;
	int eggs;
	int nurse;
};

#endif /* ANIMALDATA_H_ */
