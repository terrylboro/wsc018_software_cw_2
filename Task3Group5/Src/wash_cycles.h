/**
 **************************************************************************************
 * Add any new wash programs to this file.
 * To add a new wash cycle:
 * 1. Add your programID to ePrograms (line ________________)
 * 2. Make an array of wash_cycle with your program data (see example line __________)
 * 3. Instantiate a wash_program object passing your array made in step 2 and the
 * program length (at the bottom of the file)
 *
 * Stage names and corresponding numbers (written on the simulator):
 *  1. EMPTY
 *  2. FILL
 *  3. HEAT
 *  4. WASH
 *  5. RINSE
 *  6. SPIN
 *  7. DRY
 *  8. COMPLETE
 **************************************************************************************
 **/ 


#include <cstring>
#include "string.h"
#define MAX_WASH_LEN 16

// Defines the motor speeds available
enum eMotorControl{
	OFF,
	SLOW,
	FAST,
};

// Defines the program buttons
enum  eButtons{
	BUTONE,
	BUTTWO,
	BUTTHREE
};

// Defines the available programs by ID
enum ePrograms{
	ProgWhite,
	ProgColour,
	// Add new program ID here (e.g. ProgEco)
	TotalProgs,
};

char cycle_num = 0; // Defines what stage the wash program is at

// Stores the data for a given stage of the program
struct wash_cycle {
	char duration;
	char motor_control;
	char status_code;
};

// Class to store the wash program data and functionality
class wash_program {
	public:
		wash_cycle get_current_wash_cycle();
		wash_program(wash_cycle *cycles, int length);
		char wash_length;
	private:
		wash_cycle cycle_array[MAX_WASH_LEN];
};

// Variables to store the program information
// MOVE TO WM.cpp
char ProgramID = 0;
int prog_num = 0;
int oldprog_num = 99;
void setProg(int button);
void startWash(int prog_num);

// Colour wash program data
// Each line corresponds to the data for 1 stage
// e.g. 5,OFF,2 corresponds to 5 second duration, motor off, and "fill"
wash_program *pCurrentProg;
wash_cycle colour_cycles[] = {
	5,OFF,2,
	2,OFF,3,
	3,SLOW,4,
	4,OFF,1,
	4,OFF,2,
	4,SLOW,5,
	3,OFF,1,
	6,FAST,6,
	5,OFF,7,
	0,OFF,8
};

// White wash program data
wash_cycle white_cycles [] = {
	5,OFF,2,
	6,OFF,3,
	4,SLOW,4,
	4,OFF,1,
	4,OFF,2,
	5,SLOW,5,
	3,OFF,1,
	8,FAST,6,
	4,SLOW,6,
	5,OFF,7,
	0,OFF,8
};

// Add new wash program data here

// Instantiate the wash programs as objects
wash_program colour_wash(colour_cycles,10);
wash_program white_wash(white_cycles,11);
// (Instantiate new wash program here)

// Add them to the array of available programs
wash_program program_array[] = {
	white_wash,
	colour_wash
	// (Add new program here)
};


// Gets the current wash cycle stage
// Arguments: none
// Returns: wash_cycle
wash_cycle wash_program::get_current_wash_cycle() {
			return cycle_array[cycle_num-1];
}

// Constructor for a wash program
// Arguments: an array of wash cycle stages and the length of the wash
// Returns: void
wash_program::wash_program(wash_cycle *cycles, int length){
			for(int i = 0; i < length; i++)
				cycle_array[i] = cycles[i];
			wash_length = length;
}

// Assign program to run
// Arguments: program number to run
// Returns: void
void startWash(int prog_num){
	if(prog_num<TotalProgs)
		pCurrentProg = &program_array[prog_num];
}