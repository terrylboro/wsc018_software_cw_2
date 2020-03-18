#include <cstring>
#include "string.h"
#define MAX_WASH_LEN 16
enum eMotorControl{
	OFF,
	SLOW,
	FAST,
};

enum  eButtons{
	BUTONE,
	BUTTWO,
	BUTTHREE
};

enum ePrograms{
	ProgWhite,
	ProgColour,
};
char cycle_num = 0;

struct wash_cycle {
	char duration;
	char motor_control;
	char status_code;
};

class wash_program {
	public:
		wash_cycle get_current_wash_cycle() {
			return cycle_array[cycle_num-1];
		}
		wash_program(wash_cycle *cycles, int length){
			for(int i = 0; i < length; i++)
				cycle_array[i] = cycles[i];
			wash_length = length;
		}
		char wash_length;
	private:
		wash_cycle cycle_array[MAX_WASH_LEN];
};


char ProgramID = 0;
int prog_num = 0;
int oldprog_num = 99;
void setProg(int button);
void startWash(int prog_num);

wash_program *pCurrentProg;
wash_cycle colour_cycles[] = {5,OFF,2,
2,OFF,3,
3,SLOW,4,
4,OFF,1,
4,OFF,2,
4,SLOW,5,
3,OFF,1,
6,FAST,6,
5,OFF,7,
0,OFF,8};

wash_cycle white_cycles [] = {5,OFF,2,
6,OFF,3,
4,SLOW,4,
4,OFF,1,
4,OFF,2,
5,SLOW,5,
3,OFF,1,
8,FAST,6,
4,SLOW,6,
5,OFF,7,
0,OFF,8};

wash_program colour_wash(colour_cycles,10);
wash_program white_wash(white_cycles,11);

