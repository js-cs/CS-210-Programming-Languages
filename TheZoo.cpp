#include <iostream>
#include <jni.h>
#include <exception>
#include <vector>
#include <fstream>
#include "AnimalData.h"

using namespace std;

// Global data set
vector<AnimalData> animalDataSet(1);

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

// Pad function used to ensure spacing is correct
string PadLeft(string inStr, int lenPad, char inChar) {
	int totalPad = lenPad - inStr.size();
	if (inStr.size() < lenPad) {
		int i;
		for (i = 0; i < totalPad; i++) {
			inStr = inChar + inStr;
		}
	}
	return inStr;
}

// Pad function used to ensure spacing is correct
string PadRight(string inStr, int lenPad, char inChar) {
	int totalPad = lenPad - inStr.size();
	if (inStr.size() < lenPad) {
		int i;
		for (i = 0; i < totalPad; i++) {
			inStr = inStr + inChar;
		}
	}
	return inStr;
}

// Function for adding an animal; prompts user inputs
AnimalData AddAnimal()
{
	// Temporary string and int for gathering data
	// AnimalData object for holding values
	string tmpStr;
	int tmpInt;
	AnimalData tmpAnimal;
	try {
		cout << "Enter tracking number (max 6 chars): ";
		getline(cin, tmpStr);
		// Ensure tracking number isn't larger than allowed
		if (tmpStr.size() > 6) {
			throw 1;
		}
		tmpAnimal.setTrackNum(PadLeft(tmpStr, 6, '0'));
		cout << "Enter animal name (max 15 chars): " << endl;
		getline(cin, tmpStr);
		// Ensure name is within 15 character constraint
		if (tmpStr.size() > 15) {
			throw 1;
		}
		tmpAnimal.setName(PadRight(tmpStr, 15, ' '));
		cout << "Enter animal type (max 15 chars): " << endl;
		getline(cin, tmpStr);
		// Ensure type is within 15 character constraint
		if (tmpStr.size() > 15) {
			throw 1;
		}
		tmpAnimal.setType(PadRight(tmpStr, 15, ' '));
		cout << "Enter animal subtype (max 15 chars): " << endl;
		getline(cin, tmpStr);
		// Ensure subtype is within 15 character constraint
		if (tmpStr.size() > 15) {
			throw 1;
		}
		tmpAnimal.setSubType(PadRight(tmpStr, 15, ' '));
		cout << "How many eggs does the animal have?" << endl;
		cin >> tmpInt;
		// Ensure eggs is 0 or more
		if (tmpInt < 0) {
			throw 1;
		}
		tmpAnimal.setEggs(tmpInt);
		cout << "Is the animal nursing? 1 for yes, 0 for no: " << endl;
		cin >> tmpInt;
		// Nursing is yes or no
		if (!(tmpInt == 0 || tmpInt == 1)) {
			throw 1;
		}
		tmpAnimal.setNurse(tmpInt);
	}
	catch (...) {
		cout << "Invalid input, returning to main menu." << endl;
		// AnimalData nullAnimal;
		// return nullAnimal;
	}

    return tmpAnimal;
}

// Function for removing an animal from the vector; prompts user input
void RemoveAnimal()
{
	// If first animal is NULL, no data has been loaded
    if (animalDataSet.at(0).getTrackNum() == "-1") {
    	cout << "No data loaded. Returning to main menu." << endl;
    }
    else {
    	try {
    		string removeNum;
    		cout << "Input tracking number of animal to be removed (include 0's): " << endl;
    		if (!(cin >> removeNum)) {
    			throw 1;
    		}
    		int i;
    		// Search for tracking number
    		for (i = 0; i < animalDataSet.size(); i++) {
    			if (animalDataSet.at(i).getTrackNum() == removeNum) {
    				// If found, erase this entry
    				animalDataSet.erase (animalDataSet.begin() + i);
    				i--;
    			}
    		}
    	}
    	catch (...) {
    		cout << "Invalid input, returning to main menu." << endl;
    		return;
    	}
    	cout << "Animal successfully removed." << endl;
    }
}

// Helper function; reads input from stream and parses into AnimalData object
AnimalData InAnimal(string inStr) {
	// tmpAnimal will be returned with parsed values
	AnimalData tmpAnimal;
	// i is for incremental search for delimiters
	// intHold is for holding ints converted from the string
	int i;
	int intHold;

	// Find first space after tracking number
	i = inStr.find_first_of(" ");
	tmpAnimal.setTrackNum(inStr.substr(0, i));

	// Reduce string size, making it easier to parse
	inStr = inStr.substr(i);

	// Find first space after name
	i = inStr.find_first_not_of(" ");
	tmpAnimal.setName(inStr.substr(i, 15));
	i = i + 15;

	// Repeat
	inStr = inStr.substr(i);

	i = inStr.find_first_not_of(" ");
	tmpAnimal.setType(inStr.substr(i, 15));
	i = i + 15;

	inStr = inStr.substr(i);

	i = inStr.find_first_not_of(" ");
	tmpAnimal.setSubType(inStr.substr(i, 15));
	i = i + 15;

	inStr = inStr.substr(i);

	i = inStr.find_first_not_of(" ");
	inStr = inStr.substr(i);
	i = inStr.find_first_of(" ");
	// stoi converts substring into int
	intHold = stoi(inStr.substr(0, i));
	tmpAnimal.setEggs(intHold);

	inStr = inStr.substr(i);

	i = inStr.find_first_not_of(" ");
	inStr = inStr.substr(i);
	i = inStr.find_first_of(" ");
	intHold = stoi(inStr.substr(0, i));
	tmpAnimal.setNurse(intHold);

	return tmpAnimal;
}

// This function loads animal data from a file and parses it to the vector
void LoadDataFromFile()
{
	ifstream inFS;
	string tmpStr;

	// Open file
	inFS.open("zoodata.txt");
	// If it fails, catch it
    if (!inFS.is_open()) {
    	cout << "Unable to open file!" << endl;
    	return;
    }
    // For each line, parse into an AnimalData object and place in global vector
	for (tmpStr; getline(inFS, tmpStr); ) {
		if (tmpStr.size() > 2) {
			if (animalDataSet.at(0).getTrackNum() == "-1") {
				animalDataSet.at(0) = InAnimal(tmpStr);
			}
			else {
				animalDataSet.push_back (InAnimal(tmpStr));
			}
		}
	}
	inFS.close();
	cout << "Data loaded!" << endl;
}

// This function saves vector data to a file
void SaveDataToFile()
{
	int i;
	string tmpStr;
	ofstream outFS;
	// Open file
    outFS.open("zoodata.txt");
    // If file fails to open, catch it
    if (!outFS.is_open()) {
    	cout << "Unable to open file!" << endl;
    	return;
    }
    // Pushes all data held in the vector to a string; new line for each entry
    for (i = 0; i < animalDataSet.size(); i++) {
    	tmpStr = tmpStr + animalDataSet.at(i).getTrackNum() + " ";
    	tmpStr = tmpStr + animalDataSet.at(i).getName() + " ";
    	tmpStr = tmpStr + animalDataSet.at(i).getType() + " ";
    	tmpStr = tmpStr + animalDataSet.at(i).getSubType() + " ";
    	tmpStr = tmpStr + to_string(animalDataSet.at(i).getEggs()) + " ";
    	tmpStr = tmpStr + to_string(animalDataSet.at(i).getNurse());
    	if (i < animalDataSet.size() - 1) {
    		tmpStr = tmpStr + "\n";
    	}
    }
    // Send string to file
    outFS << tmpStr;
    outFS.close();
    cout << "Data saved!" << endl;
}

// Simple menu display
void DisplayMenu()
{
     cout << "*****************************************************************" << endl;
     cout << "Options: " << endl;
     cout << "1. Load Animal Data" << endl;
     cout << "2. Generate Data" << endl;
     cout << "3. Display Animal Data" << endl;
     cout << "4. Add Record" << endl;
     cout << "5. Delete Record" << endl;
     cout << "6. Save Animal Data" << endl;
     cout << "7. Quit" << endl;
}



int main()
{
	// User inputs
	int inputs = 0;

	// Evaluate user input; if 7, quit
	while (inputs != 7) {
		DisplayMenu();
		// Catch invalid inputs
		try {
			if (!(cin >> inputs)) {
				throw 1;
			}
		}
		catch (...) {
			cout << "Invalid input, ending program.";
			return 0;
		}
		// Allows for use of getline() later
		cin.ignore();
		switch(inputs) {
			case 1 :
				// Load Animal Data
				// Check if data is already loaded
				if (!(animalDataSet.at(0).getTrackNum().compare("-1") == 0)) {
					cout << "Data set already loaded, are you sure you want to reload (y/n)?";
					string tmpStr;
					cin >> tmpStr;
					if (tmpStr == "y" || tmpStr == "Y") {
						animalDataSet.clear();
						AnimalData nullAnimal;
						animalDataSet.push_back (nullAnimal);
					}
				}
				LoadDataFromFile();
				break;
			case 2 :
				// Use Java function to generate data
				GenerateData();
				break;
			case 3 :
				// Display Animal Data
				// If none currently in system, tell user
				if (animalDataSet.at(0).getTrackNum() == "-1") {
					cout << "No data input or loaded, returning to main menu." << endl;
				}
				else {
					int i;
					cout << "Track #| Name            | Animal Type     | Animal Subtype  |Eggs|Nursing" << endl;
					cout << "--------------------------------------------------------------------------" << endl;
					for (i = 0; i < animalDataSet.size(); i++) {
						animalDataSet.at(i).print();
					}
				}
				break;
			case 4 :
				// Add Record
			    if (animalDataSet.at(0).getTrackNum() == "-1") {
			    	animalDataSet.at(0) = AddAnimal();
			    }
			    else {
			    	animalDataSet.push_back (AddAnimal());
			    }
			    cout << "Animal added!" << endl;
				break;
			case 5 :
				// Delete Record
				RemoveAnimal();
				break;
			case 6 :
				// Save Animal Data
				SaveDataToFile();
				break;
			case 7 :
				// Quit
				cout << "Ending program..." << endl;
				break;
			default :
				// Invalid inputs - reset inputs variable and go back to main menu
				cout << "Invalid input." << endl;
				inputs = 0;
		}
	}

	return 1;
}
