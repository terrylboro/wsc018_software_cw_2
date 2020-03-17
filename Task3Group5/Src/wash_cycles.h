#include <cstring>

enum  Buttons{
	BUTONE,
	BUTTWO,
	BUTTHREE
};

int prog_num = 0;
int oldprog_num = 0;

void setProg(int button);

char colour_wash_cycle[10][20] = {"fill", "heat", "wash_slow", "empty", "fill", "rinse_slow", "empty", "spin_high", "dry", "complete"};
int colour_wash_duration[] = {5, 2, 3, 4, 4, 4, 3, 6, 5, 0};

char white_wash_cycle[11][20] = {"fill", "heat", "wash_slow", "empty", "fill", "rinse_slow", "empty", "spin_high", "spin_slow", "dry", "complete"};
int white_wash_duration[] = {5, 6, 4, 4, 4, 5, 3, 8, 4, 5, 0};

int get_num_cycle_stages(int cycle_num)
{
	int array_length;
	switch(cycle_num)
	{
		case 0:
			array_length = (sizeof(colour_wash_duration)) / (sizeof(colour_wash_duration[0]));
            break;
		case 1:
			array_length = sizeof(white_wash_duration)/sizeof(white_wash_duration[0]);
			break;
		default:
			array_length = 0;
	}
	return array_length;
}

int *get_wash_duration(int cycle_num)
{
	int *wash_duration;
	switch(cycle_num)
	{
		case 0:
			wash_duration = colour_wash_duration;
		case 1:
			wash_duration = white_wash_duration;
	}
	return wash_duration;
}

char *get_wash_cycle(int cycle_num)
{
	char *wash_cycle;
	switch(cycle_num)
	{
		case 0:
			//wash_cycle = colour_wash_cycle;
			std::strcpy(wash_cycle, *colour_wash_cycle);
		case 1:
			//wash_cycle = white_wash_cycle;
			std::strcpy(wash_cycle, *white_wash_cycle);
	}
	return wash_cycle;
}
