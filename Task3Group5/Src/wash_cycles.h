#include <iostream>

std::string colour_wash_cycle[] = {"fill", "heat", "wash_slow", "empty", "fill", "rinse_slow", "empty", "spin_high", "dry", "complete"};
int colour_wash_duration[] = {5, 2, 3, 4, 4, 4, 3, 6, 5, 0};

std::string white_wash_cycle[] = {"fill", "heat", "wash_slow", "empty", "fill", "rinse_slow", "empty", "spin_high", "spin_slow", "dry", "complete"};
int white_wash_duration[] = {5, 6, 4, 4, 4, 5, 3, 8, 4, 5, 0};

int get_num_cycle_stages(int cycle_num)
{
	int array_length;
	switch(cycle_num)
	{
		case 0:
			array_length = sizeof(colour_wash_duration)/sizeof(*colour_wash_duration);
		case 1:
			array_length = sizeof(white_wash_duration)/sizeof(*white_wash_duration);
		default:
			array_length = 0;
		return array_length;
	}
}

int *get_wash_duration(int cycle_num)
{
	switch(cycle_num)
	{
		case 0:
			return colour_wash_duration;
		case 1:
			return white_wash_duration;
	}
}

std::string *get_wash_cycle(int cycle_num)
{
	switch(cycle_num)
	{
		case 0:
			return colour_wash_cycle;
		case 1:
			return white_wash_cycle;
	}
}
