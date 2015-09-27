//***************************************************************************
//  FILENAME:	 AllenAssn4.cpp
//  DESCRIPTION: Program that will implement the following. 
// 				 1. 
//				 2. 
//				 3. 
//				 4. 
//				 5. 
//
//  DATE:        9/10/15
//  CLASS/TERM:  CS362_X40_Data Structures - CU_CS362 - XIN_X40_15F8W1
//  DESIGNER:	 Andrae Allen
//  FUNCTIONS:	 main - reads values, performs calculations, & displays results
//               ProgramDescription - Displays a brief discription of the program
//				 xxxxxxxxxxxxxxxxxx - 
//				 xxxxxxxxxxxxxxxxxx - 
//***************************************************************************

#include <iostream> 
#include <fstream>
#include <cstdio> 
#include <iomanip>
#include <string>

using namespace std;

enum personnel { LAWYER, PARALEGAL, ASSISTANT, EMPTY };


struct BuildingSchematic
{
	int floor;
	string Office;
	personnel occupantType;
};

const int NUM_OF_FLOORS = 5;
const int OFICES_PER_FLOOR = 8;
const int IGNORE_AMOUNT = 100;
const string INPUT_FILE_NAME = "BUILDING.bin"; // File name for input file

void ProgramDescription();
void InitializeBldg2Empty(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR]);
void readAndSortData(string inputFileName);

void showBuidlingConfig(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR]);
string convert2UpperCase(string stringInput);

string statusModMunu();


int main()
{
	string OptionDesired; 
	BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR];

	// Initialize a two-dimensional array, representing the offices in the building, to all EMPTY offices.
	InitializeBldg2Empty(officeBuilding);

	readAndSortData(INPUT_FILE_NAME);

	showBuidlingConfig(officeBuilding);

	
	
	do
	{
		OptionDesired = statusModMunu();


	}

	// While response does not equal exit  
	while (OptionDesired != "D");
	system("PAUSE");
	return 0;
}


void ProgramDescription()
{

	cout << "Program to implement the following:" << endl;
	cout << "1. Check for BUILDING.BIN file upon first opening" << endl;



}

void InitializeBldg2Empty(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR])
{
	int itemCounter = 0; 
	

	for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
	{
		for (int columnPosition = 0; columnPosition < OFICES_PER_FLOOR; columnPosition++)
		{
			officeBuilding[rowPosition][columnPosition].occupantType = EMPTY;
			itemCounter++;
		}
	}

	/*
	for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
	{
		for (int columnPosition = 0; columnPosition < OFICES_PER_FLOOR; columnPosition++)
		{
			cout << officeBuilding[rowPosition][columnPosition].occupantType << endl; 
		}
	}
	
	cout << itemCounter << endl; 

	*/
}

void readAndSortData(string inputFileName)
{
	bool fileOpenSuccess;

	ifstream inputFile; // input file stream variable
	inputFile.open(inputFileName.c_str());

	if (!inputFile)
	{
		fileOpenSuccess = false;
		cout << endl;
		cerr << "Error! System could not open file named \"" << inputFileName << "\"" << endl;


	

	}
}

void showBuidlingConfig(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR])
{
	for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
	{
		for (int columnPosition = 0; columnPosition < OFICES_PER_FLOOR; columnPosition++)
		{
			

			//officeBuilding[rowPosition][columnPosition].occupantType = EMPTY;
			
		}
	}

}

string statusModMunu()
{
		string response2Question;			// Response to question
		bool repeatQuestion;				// Repeat question
		do {

			cout << endl;
			cout << "Please choose an option by entering its corresponding character" << endl;
			cout << "1 - Change office from occupied to empty " << endl;
			cout << "2 - Modify office occupant type" << endl;
			cout << "3 - Change office from empty to occupied" << endl;
			cout << "D - Done making modifications" << endl;
			cout << endl;
			cout << "Please enter response here: ";
			cin >> response2Question;
			cin.ignore(IGNORE_AMOUNT, '\n');

			response2Question = convert2UpperCase(response2Question);


			if ((response2Question != "1") && (response2Question != "2") && (response2Question != "3") && (response2Question != "D"))
			{
				cout << endl;
				cout << "ERROR! Unrecognized input, please try again." << endl;
				cout << endl;
				repeatQuestion = true;
			}

			else
			{
				repeatQuestion = false;
			}
		}

		// while repeat question equals true
		while (repeatQuestion == true);


		return response2Question;




}

void empty2occupied(string optionSelected){	cout << "You selected" << optionSelecetd << "Change office from empty to occupied" << endl; }

void occupied2Empty(string optionSelected){}
void getFloorNumber()
{

}


string convert2UpperCase(string stringInput)
{
	int i = 0;  // variabel used for tracking index location in array
	char c;		// variable used to temporaliy store character from string

	string upperCasedString;		// A string where all the letters are uppercase  

	while (stringInput[i] != '\0')
	{
		// if character is a letter 
		if (isalpha(stringInput[i]))
		{
			c = stringInput[i];
			stringInput[i] = toupper(c);
			i++;
		}

		else
		{
			i++;
		}

	}

	upperCasedString = stringInput;

	return upperCasedString;

}
