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

struct OccupantStats
{
	int lawyerCount; 
	int paralegalCount;
	int assistantsCount;
	int occupiedOffices;
	int emptyOffices; 
};

const int LOW_FLOOR = 0;
const int HIGH_FLOOR = 4; 

const int NUM_OF_FLOORS = 5;
const int OFICES_PER_FLOOR = 8;
const int TOTAL_OFFICES = 40; 
const int IGNORE_AMOUNT = 999;
const string INPUT_FILE_NAME = "BUILDING.bin"; // File name for input file

void ProgramDescription();
void InitializeBldg2Empty(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR]);
void readAndSortData(string inputFileName);

void  updateBuidlingStats(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR], OccupantStats& OccupantStatistics);
void empty2Occupied(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR], OccupantStats& OccupantStatistics);
void occupied2Empty(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR], OccupantStats& OccupantStatistics);

string convert2UpperCase(string stringInput);
int getFloorNumber(int min, int max);
string  getOfficeLetter();
personnel getOccupantType();

string statusModMunu();


int main()
{
	int occupiedOfficeCount = 0;
	string OptionDesired; 
	BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR];
	OccupantStats OccupantStatistics; 

	// Initialize a two-dimensional array, representing the offices in the building, to all EMPTY offices.
	InitializeBldg2Empty(officeBuilding);

	readAndSortData(INPUT_FILE_NAME);

	updateBuidlingStats(officeBuilding, OccupantStatistics);

	
	do
	{
		OptionDesired = statusModMunu();

		occupied2Empty(OptionDesired, officeBuilding, OccupantStatistics);
		empty2Occupied(OptionDesired, officeBuilding, OccupantStatistics);
	

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

void updateBuidlingStats(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{
	OccupantStatistics.lawyerCount = 0; 
	OccupantStatistics.paralegalCount = 0; 
	OccupantStatistics.assistantsCount = 0; 
	OccupantStatistics.emptyOffices = 0; 
	OccupantStatistics.occupiedOffices = 0; 

	for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
	{
		for (int columnPosition = 0; columnPosition < OFICES_PER_FLOOR; columnPosition++)
		{


			if (officeBuilding[rowPosition][columnPosition].occupantType == LAWYER)
			{
				OccupantStatistics.lawyerCount++;
			}

			else if (officeBuilding[rowPosition][columnPosition].occupantType == PARALEGAL)
			{
				OccupantStatistics.paralegalCount++;
			}

			else if (officeBuilding[rowPosition][columnPosition].occupantType == PARALEGAL)
			{
				OccupantStatistics.assistantsCount++;
			}

			else if (officeBuilding[rowPosition][columnPosition].occupantType == EMPTY)
			{
				OccupantStatistics.emptyOffices++;
			}
		}

	}

	OccupantStatistics.occupiedOffices = TOTAL_OFFICES - OccupantStatistics.emptyOffices;

	/*
	cout << "Lawyer Count    = " << OccupantStatistics.lawyerCount << endl; 
	cout << "ParaLegal Count = " << OccupantStatistics.paralegalCount << endl;
	cout << "Assistant Count = " << OccupantStatistics.assistantsCount << endl;
	cout << "ParaLegal Count = " << OccupantStatistics.paralegalCount << endl; 
	cout << "Total Occupied  = " << OccupantStatistics.occupiedOffices << endl; 
	cout << "Total Empty = " << OccupantStatistics.emptyOffices << endl; 
	*/

}

void showBuidlingConfig(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR], personnel OccupantType)
{
	for (int rowPosition = HIGH_FLOOR; rowPosition >= 0; rowPosition--)
	{
		for (int columnPosition = 0; columnPosition < OFICES_PER_FLOOR; columnPosition++)
		{

			if (OccupantType == EMPTY)
			{
				if (officeBuilding[rowPosition][columnPosition].occupantType == OccupantType)
				{

					cout << setw(5) << rowPosition << char(columnPosition + 65);
					if (char(columnPosition + 65) == 'H')
					{
						cout << endl;
					}
				}

				else if (officeBuilding[rowPosition][columnPosition].occupantType != OccupantType)
				{
					cout << setw(6) << "--";
					if (char(columnPosition + 65) == 'H')
					{
						cout << endl;
					}
				}
			}

			
			else if (OccupantType != EMPTY)
			{
				cout << "here!!!!!!!!!!!!!!!!!!" << endl; 
				if (officeBuilding[rowPosition][columnPosition].occupantType != EMPTY)
				{

					cout << setw(5) << rowPosition << char(columnPosition + 65);
					if (char(columnPosition + 65) == 'H')
					{
						cout << endl;
					}

					else if (officeBuilding[rowPosition][columnPosition].occupantType == EMPTY)
					{
						cout << setw(6) << "--";
						if (char(columnPosition + 65) == 'H')
						{
							cout << endl;
						}
					}
				}
			}
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

void occupied2Empty(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{
	cout << "See Below for a Buiding map depicting the occupied offices" << endl << endl;

	if ((optionSelected == "1") && (OccupantStatistics.emptyOffices != 40))
	{
		int floorNumber;
		string officeLetter;
		personnel OccupantType;

		cout << "IN OCUPIED" << endl; 
		showBuidlingConfig(officeBuilding, LAWYER);
	}
}

void empty2Occupied(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{
	cout << "See Below for a Buiding map depicting the empty offices" << endl << endl;

	if ((optionSelected == "3") && (OccupantStatistics.emptyOffices > 0))
	{
		int floorNumber;
		string officeLetter;
		personnel OccupantType;

		showBuidlingConfig(officeBuilding, EMPTY);

		floorNumber = getFloorNumber(LOW_FLOOR, HIGH_FLOOR);
		officeLetter = getOfficeLetter();
		OccupantType = getOccupantType();

		officeBuilding[floorNumber][(((int) officeLetter[0]) - 65)].occupantType = OccupantType;
		
		updateBuidlingStats(officeBuilding, OccupantStatistics);



	}

	else if (OccupantStatistics.emptyOffices == 0)
	{
		cout << "ERROR! the buiding does not have an empty office available" << endl;
	}


	
}



int getFloorNumber(int min, int max)
{
	int num;
	int errorCounter = 0;

	do
	{
		cout << endl; 
		cout << "Please enter a floor number " << min << " - " << max << ": ";
		cin >> num;
		cin.ignore(IGNORE_AMOUNT, '\n');


		if ((cin.fail()) || (num < min) || (num> max))
		{
			cin.clear();
			cin.ignore(IGNORE_AMOUNT, '\n');
			errorCounter++;
			cout << "Error! you did not enter a valid floor. A valid floor is " << min << " - " << max << " Try again." << endl;
		}
	}



	while (errorCounter > 0);


	return num;
	
}

string  getOfficeLetter()
{
	
	string officeLetterEntered;
	int errorCounter;

	do
	{
		errorCounter = 0;
		cout << "Please choose an office letter A - H : ";
		cin >> officeLetterEntered; 
		officeLetterEntered = convert2UpperCase(officeLetterEntered);

		if ((officeLetterEntered != "A") && (officeLetterEntered != "B") && (officeLetterEntered != "C") && (officeLetterEntered != "D") &&
			(officeLetterEntered != "E") && (officeLetterEntered != "F") && (officeLetterEntered != "G") && (officeLetterEntered != "H"))
			
		{
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			cout << endl;
			errorCounter++;
		}

	}
		while (errorCounter > 0);

	
	return officeLetterEntered; 

}

personnel getOccupantType()
{
	int errorCounter;
	string occupantTypeEntered;
	
	personnel jobTitle; 

	do
	{
		errorCounter = 0;
		cout << "Please choose an occupant Type" << endl;
		cout << "L = Lawyer " << endl;
		cout << "P = Paralegal " << endl;
		cout << "A = Assistant" << endl;
		cout << "Enter Office Type Here: "; 
		cin >> occupantTypeEntered;
		occupantTypeEntered = convert2UpperCase(occupantTypeEntered);

		if ((occupantTypeEntered != "L") && (occupantTypeEntered != "P") && (occupantTypeEntered != "A"))
		{
			cin.clear();
			cin.ignore(IGNORE_AMOUNT, '\n');
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			cout << endl;
			errorCounter++;
		}


	}
		
	while (errorCounter > 0);

	if (occupantTypeEntered == "L")
	{
		jobTitle = LAWYER; 
	}

	else if (occupantTypeEntered == "P")
	{
		jobTitle = PARALEGAL;
	}

	else if (occupantTypeEntered == "A")
	{
		jobTitle = ASSISTANT;
	}


	return jobTitle; 


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

