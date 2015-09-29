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
//               InitializeBldg2Empty- Displays a brief discription of the program
//				 readAndSortData - 
//				 updateBuidlingStats - 
//				 empty2Occupied -
//				 xxxxxxxxxxxxxxxxxx -
//				 xxxxxxxxxxxxxxxxxx -
//				 xxxxxxxxxxxxxxxxxx -
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

const int LOW_FLOOR = 0;			// Lowest floor in building
const int HIGH_FLOOR = 4;			// Highest Floor in building

const int NUM_OF_FLOORS = 5;		// Total number of floors 
const int OFFICES_PER_FLOOR = 8;	// Offices per floor
const int TOTAL_OFFICES = 40;		// Total Offices 
const int IGNORE_AMOUNT = 999;		// Ignore amount

const int SET_WIDTH_5 = 5;
const int SET_WIDTH_6 = 6;
const int SET_WIDTH_7 = 7; 
const int ASCII_CONSTANT = 65;

const string INPUT_FILE_NAME = "BUILDING.bin";		// File name for input file
const string OUTPUT_FILE_NAME = "BUILDING.bin";		// File name for output file

void ProgramDescription();
void InitializeBldg2Empty(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR]);
void readAndSortData(string inputFileName, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR]);

void updateBuidlingStats(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics);
void empty2Occupied(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics);
void occupied2Empty(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics);
void modifyOccupantType(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics);
void DoneMakingMods(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics);
void displayBuildingstats(OccupantStats& OccupantStatistics);

string convert2UpperCase(string stringInput);
int getFloorNumber(int min, int max);
string getOfficeLetter();
personnel getOccupantType();
string personnelAsString(personnel OccupantEnumForm);
string statusModMunu();





int main()
{
	int occupiedOfficeCount = 0;
	string OptionDesired; 
	BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR];
	OccupantStats OccupantStatistics; 

	// Initialize a two-dimensional array, representing the offices in the building, to all EMPTY offices.
	InitializeBldg2Empty(officeBuilding);

	readAndSortData(INPUT_FILE_NAME, officeBuilding);

	updateBuidlingStats(officeBuilding, OccupantStatistics);
	displayBuildingstats(OccupantStatistics);

	
	do
	{
		OptionDesired = statusModMunu();

		occupied2Empty(OptionDesired, officeBuilding, OccupantStatistics);
		modifyOccupantType(OptionDesired, officeBuilding, OccupantStatistics);
		empty2Occupied(OptionDesired, officeBuilding, OccupantStatistics);
		DoneMakingMods(OptionDesired, officeBuilding, OccupantStatistics);
		
	

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

void InitializeBldg2Empty(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR])
{
	int itemCounter = 0; 
	

	for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
	{
		for (int columnPosition = 0; columnPosition < OFFICES_PER_FLOOR; columnPosition++)
		{
			officeBuilding[rowPosition][columnPosition].occupantType = EMPTY;
			itemCounter++;
		}
	}

	/*
	for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
	{
		for (int columnPosition = 0; columnPosition < OFFICES_PER_FLOOR; columnPosition++)
		{
			cout << officeBuilding[rowPosition][columnPosition].occupantType << endl; 
		}
	}
	
	cout << itemCounter << endl; 

	*/
}

void readAndSortData(string inputFileName, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR])
{
	bool fileOpenSuccess;

	ifstream buildingConfigFile; // input file stream variable

	buildingConfigFile.open(inputFileName, ios::binary | ios::in);

	if (!buildingConfigFile)
	{
		fileOpenSuccess = false;
		cout << endl;
		cerr << "Error! System could not open file named \"" << inputFileName << "\"" << endl;

	}

	else
	{

		for (int rowPosition = 0; ((rowPosition < NUM_OF_FLOORS) && (buildingConfigFile)); rowPosition++)
		{
			for (int columnPosition = 0; ((columnPosition < OFFICES_PER_FLOOR) && (buildingConfigFile)); columnPosition++)
			{
				buildingConfigFile.read(reinterpret_cast<char*>(&officeBuilding[rowPosition][columnPosition]), sizeof(BuildingSchematic));
			}
		}

		buildingConfigFile.close();

	}
}

void updateBuidlingStats(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{
	OccupantStatistics.lawyerCount = 0; 
	OccupantStatistics.paralegalCount = 0; 
	OccupantStatistics.assistantsCount = 0; 
	OccupantStatistics.emptyOffices = 0; 
	OccupantStatistics.occupiedOffices = 0; 

	for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
	{
		for (int columnPosition = 0; columnPosition < OFFICES_PER_FLOOR; columnPosition++)
		{


			if (officeBuilding[rowPosition][columnPosition].occupantType == LAWYER)
			{
				OccupantStatistics.lawyerCount++;
			}

			else if (officeBuilding[rowPosition][columnPosition].occupantType == PARALEGAL)
			{
				OccupantStatistics.paralegalCount++;
			}

			else if (officeBuilding[rowPosition][columnPosition].occupantType == ASSISTANT)
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

void showBuidlingConfig(BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], personnel OccupantType)
{


	for (int rowPosition = HIGH_FLOOR; rowPosition >= 0; rowPosition--)
	{
		for (int columnPosition = 0; columnPosition < OFFICES_PER_FLOOR; columnPosition++)
		{

			if (OccupantType == EMPTY)
			{
				if (officeBuilding[rowPosition][columnPosition].occupantType == OccupantType)
				{

					cout << setw(SET_WIDTH_5) << rowPosition << char(columnPosition + ASCII_CONSTANT);
					if (char(columnPosition + ASCII_CONSTANT) == 'H')
					{
						cout << endl;
					}
				}

				else if (officeBuilding[rowPosition][columnPosition].occupantType != OccupantType)
				{
					cout << setw(SET_WIDTH_6) << "--";
					if (char(columnPosition + ASCII_CONSTANT) == 'H')
					{
						cout << endl;
					}
				}
			}

			
			else if (OccupantType != EMPTY)
			{

				if (officeBuilding[rowPosition][columnPosition].occupantType != EMPTY)
				{
	
					cout << setw(SET_WIDTH_6) << rowPosition << char(columnPosition + ASCII_CONSTANT);
				}
					
				else if (officeBuilding[rowPosition][columnPosition].occupantType == EMPTY)
					{
						cout << setw(SET_WIDTH_6) << "--";
					}
				

				if (char(columnPosition + ASCII_CONSTANT) == 'H')
				{
					
					cout << endl;
				}



			}
		}
	}
}

void displayBuildingstats(OccupantStats& OccupantStatistics)
{
	int workerCount; 
	int totalOffices;
	
	cout << endl; 
	cout << "Current Building Statistics" << endl; 
	cout << setw(SET_WIDTH_7) << OccupantStatistics.lawyerCount << " Lawyers" << endl;
	cout << setw(SET_WIDTH_7) << OccupantStatistics.paralegalCount << " Paralegals" << endl;
	cout << setw(SET_WIDTH_7) << OccupantStatistics.assistantsCount << " Assistants" << endl;
	cout << setw(SET_WIDTH_7) << "---" << endl;

	workerCount = OccupantStatistics.lawyerCount + OccupantStatistics.paralegalCount + OccupantStatistics.assistantsCount;
	totalOffices = NUM_OF_FLOORS * OFFICES_PER_FLOOR;


	cout << setw(SET_WIDTH_7) << workerCount << " occupied offices" << endl;
	cout << setw(SET_WIDTH_7) << totalOffices - workerCount << " empty offices" << endl;
	cout << setw(SET_WIDTH_7) << totalOffices << " Total offices" << endl;

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

void occupied2Empty(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{
	

	if ((optionSelected == "1") && (OccupantStatistics.emptyOffices != TOTAL_OFFICES))
	{
		cout << "See Below for a Buiding map depicting the occupied offices" << endl << endl;

		int floorNumber;
		string officeLetter;
		personnel OccupantType;

		showBuidlingConfig(officeBuilding, LAWYER);

		do
		{
			floorNumber = getFloorNumber(LOW_FLOOR, HIGH_FLOOR);
			officeLetter = getOfficeLetter();
			OccupantType = getOccupantType();

			if (OccupantType != EMPTY)
			{
				cout << "ERROR! Only an occupant type of Empty can be selected " << endl;
			}
		}

		while (OccupantType != EMPTY);

		officeBuilding[floorNumber][(((int)officeLetter[0]) - ASCII_CONSTANT)].occupantType = OccupantType;
		updateBuidlingStats(officeBuilding, OccupantStatistics);

		cout << endl;
		cout << "Success!  Office " << floorNumber << officeLetter << " is now empty." << endl;
		displayBuildingstats(OccupantStatistics);

	}



	else if ((optionSelected == "1") && (OccupantStatistics.emptyOffices == TOTAL_OFFICES))
	{
		cout << "ERROR! The buiding does not have any occupied offices" << endl;
	}
}


void modifyOccupantType(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{
	
	

	if ((optionSelected == "2") && (OccupantStatistics.emptyOffices != TOTAL_OFFICES))
	{
		cout << "See Below for a Buiding map depicting the occupied offices" << endl << endl;

		int floorNumber;
		string officeLetter;
		personnel OccupantType;

		showBuidlingConfig(officeBuilding, LAWYER);

		do
		{
			floorNumber = getFloorNumber(LOW_FLOOR, HIGH_FLOOR);
			officeLetter = getOfficeLetter();
			OccupantType = getOccupantType();

			if ((OccupantType == EMPTY) || (officeBuilding[floorNumber][(((int)officeLetter[0]) - ASCII_CONSTANT)].occupantType == EMPTY))
			{
				cout << "ERROR! This option only allows occupant to occupant modifications" << endl;
				cout << "This means you cannot modify an office that is already empty," << endl;
				cout << "and you cannot change an existing occupant to empty. Try again.4" << endl; 
			}
		}

		while ((OccupantType == EMPTY) || (officeBuilding[floorNumber][(((int)officeLetter[0]) - ASCII_CONSTANT)].occupantType == EMPTY));

		officeBuilding[floorNumber][(((int)officeLetter[0]) - ASCII_CONSTANT)].occupantType = OccupantType;
		updateBuidlingStats(officeBuilding, OccupantStatistics);

		cout << "Success!  Office " << floorNumber << officeLetter << " is now occupied  by a " << personnelAsString(OccupantType) << endl;
		displayBuildingstats(OccupantStatistics);
	}

	else if ((optionSelected == "2") && (OccupantStatistics.emptyOffices == TOTAL_OFFICES))
	{
		cout << "ERROR! The buiding is completely empty" << endl;
		cout << "Therefore occupant to occupant modifications cannot be made" << endl; 
	}


}




void empty2Occupied(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{
	

	if ((optionSelected == "3") && (OccupantStatistics.emptyOffices > 0))
	{
		cout << "See Below for a Buiding map depicting the empty offices" << endl << endl;

		int floorNumber;
		string officeLetter;
		personnel OccupantType;

		showBuidlingConfig(officeBuilding, EMPTY);

		do
		{
			floorNumber = getFloorNumber(LOW_FLOOR, HIGH_FLOOR);
			officeLetter = getOfficeLetter();
			OccupantType = getOccupantType();

			if (OccupantType == EMPTY)
			{
				cout << "ERROR! The office you selected is already empty. Try Again." << endl;
			}

		}

		while (OccupantType == EMPTY);


		officeBuilding[floorNumber][(((int)officeLetter[0]) - ASCII_CONSTANT)].occupantType = OccupantType;
		
		updateBuidlingStats(officeBuilding, OccupantStatistics);

		cout << "Success!  Office " << floorNumber << officeLetter << " is now occupied  by a " << personnelAsString(OccupantType) << endl;
		displayBuildingstats(OccupantStatistics);


	}

	else if ((optionSelected == "3") && (OccupantStatistics.emptyOffices == 0))
	{
		cout << "ERROR! the buiding does not have an empty office available" << endl;
	}

	
}

void  DoneMakingMods(string& optionSelected, BuildingSchematic officeBuilding[NUM_OF_FLOORS][OFFICES_PER_FLOOR], OccupantStats& OccupantStatistics)
{

	if (optionSelected == "D")
	{
		ofstream buildingConfigFile;

		buildingConfigFile.open(OUTPUT_FILE_NAME, ios::binary | ios::out);

		for (int rowPosition = 0; rowPosition < NUM_OF_FLOORS; rowPosition++)
		{
			for (int columnPosition = 0; columnPosition < OFFICES_PER_FLOOR; columnPosition++)
			{
				buildingConfigFile.write(reinterpret_cast<char*>(&officeBuilding[rowPosition][columnPosition]), sizeof(BuildingSchematic));
			}
		}
		


		buildingConfigFile.close();
		
		cout << "Changes have been saved to file, the program will now exit." << endl; 

		displayBuildingstats(OccupantStatistics);
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
		cout << "E = Empty" << endl;
		cout << "Enter Office Type Here: "; 
		cin >> occupantTypeEntered;
		occupantTypeEntered = convert2UpperCase(occupantTypeEntered);

		if ((occupantTypeEntered != "L") && (occupantTypeEntered != "P") && (occupantTypeEntered != "A") && (occupantTypeEntered != "E"))
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

	else if (occupantTypeEntered == "E")
	{
		jobTitle = EMPTY;
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

string personnelAsString (personnel OccupantEnumForm)
{
	string jobTitle;

	if (OccupantEnumForm == LAWYER)
	{
		jobTitle = "Lawyer";
	}

	else if (OccupantEnumForm == PARALEGAL)
	{
		jobTitle = "Paralegal";
	}

	else if (OccupantEnumForm == ASSISTANT)
	{
		jobTitle = "Assistant";
	}

	else if (OccupantEnumForm == EMPTY)
	{
		jobTitle = "Empty";
	}

	return jobTitle;

}
