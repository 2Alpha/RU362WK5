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
const string INPUT_FILE_NAME = "BUILDING.bin"; // File name for input file

void ProgramDescription();
void InitializeBldg2Empty(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR]);
void readAndSortData(string inputFileName);

void showBuidlingConfig(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR]);

//readAndSortData()


int main()
{
	
	BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR];

	// Initialize a two-dimensional array, representing the offices in the building, to all EMPTY offices.
	InitializeBldg2Empty(officeBuilding);

	readAndSortData(INPUT_FILE_NAME);

	showBuidlingConfig(officeBuilding);

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