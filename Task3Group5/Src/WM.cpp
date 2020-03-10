/**
 ***************************************************************************************
 * File Name          : WM.cpp
 * Description        : Application to demonstrate interaction with the
 *                      washing machine simulator
 * Authors						: Terry Fawden B719064, Leo Garroch B627709, James Hearsum B723105
 * Last Edited				: 21/02/2020
 ***************************************************************************************
 **/

 /* Configuration of the STM32 Discovery board
 */
#include <iostream>
extern "C" {  // this is needed to make C++ and C work together
  #include "gpio_setup.h"
	#include "port_map.h"
	#include "pin_map.h"
	#include "wash_cycles.h"
}


// define a delay of 1000 milliseconds and constants for motor direction
#define DELAY 1000
#define CLOCKWISE 0
#define ANTICLOCKWISE 1

/**
 ***************************************************************************************
 * Define classes corresponding to each physical component
 * In addition, the timer class which will be used to time
 * processes in task 3
 ***************************************************************************************
 **/

class Door
{
	public:
		Door();
		int ReadDoorPort();
	private:
		uint16_t port_map; // port location
		bool port_value; // stores whether door is open or closed
};

class Motor
{
	public:
		Motor();
		void Rotate(bool direction);
		void Stop();
	private:
		uint16_t port_map; // port location
		bool direction; // stores direction motor is spinning
};

class Button
{
	public:
		Button(uint16_t port);
		bool GetButtonState();
	private:
		uint16_t port_map; // port location
		bool state; // stores whether button is being pressed or not
};

class Display
{
	public:
		void UpdateDisplay(uint16_t digit);
		void DisplayNumber(int number);
	private:
		uint16_t port_map; // port location
		bool port_value; // digit displayed
};

class Buzzer
{
	public:
		void SoundBuzzer();
	private:
		uint16_t port_map; // port location
};

class Timer
{
	public:
		int GetTimeCount(void);
		void SetTimeCount(int time = 1); // set default timer to 1 second
		void Delay(uint16_t time = DELAY); // set default delay time to that defined at the top of the program
		void SetInterupt(bool);
	private:
		int time_count; // stores the current count on the timer
};

// Function prototype for CheckButtonPressed (description in funtion definition)
void CheckButtonPressed(Button AcceptButton, Button CancelButton, Display Display1, Button ProgramSelect1, Button ProgramSelect2, Button ProgramSelect3, Door Door1, Buzzer Buzz);

/**
 **************************************************************************************
 * Struct for program cycles
 **************************************************************************************
 **/

/*class WM_Program
{
	WM_Program(int prog_num);
	int *wash_cycle;
	char *wash_duration;
	string colour_wash_cycle[2] = {"fill", "heat", "wash_slow", "empty", "fill", "rinse_slow", "empty", "spin_high", "dry", "complete"};
	int colour_wash_duration[];
	char white_wash_cycle[];
	int white_wash_duration[];
	int prog_num_count;
};*/


/**
 **************************************************************************************
 * The main application code to demonstrate driver functionality                               
 **************************************************************************************
 **/

int main(void) {
	
  // STM32F3 Discovery Board initialization
  board_setup();
	// Initialise each of the components of the washing machine as objects
	Door Door1;
	Motor Motor1;
	Display Display1;
	Button AcceptButton(ACCEPT_BUTTON);
	Button CancelButton(CANCEL_BUTTON);
	Button ProgramSelect1(PROG_SEL_1);
	Button ProgramSelect2(PROG_SEL_2);
	Button ProgramSelect3(PROG_SEL_3);
	Buzzer Buzz;
	
	/* Create an array/lookup table to store stage times */
	

	while(1)
	{
		// Allow the user to select program using the program selector buttons until they press accept
		while (!AcceptButton.GetButtonState())
		{
			// Make function to log presses of PS buttons to make binary counter
			// Enter a loop when one of them is pressed which doesn't break until accept/cancel is pressed
			if (ProgramSelect1.GetButtonState())
			{
				if (AcceptButton.GetButtonState())
				{
					
				}
			}
			else if (ProgramSelect2.GetButtonState())
			{
				
			}
			else if (ProgramSelect3.GetButtonState())
			{
				
			}
			
		}
		
		// Process chosen program
		int num_prog_stages = get_num_cycle_stages(cycle_num);
		wash_duration = get_wash_duration(int cycle_num);
		wash_cycle = get_wash_cycle(int cycle_num);
		
		// Check if door is open, if so sound buzzer + don't allow to continue
		while (Door1.ReadDoorPort())
		{
			Buzz.SoundBuzzer();
		}
		// Set timer to the correct length
		Timer Timer1;
		
		
		// Update program status and display on 7 segment display
		
		
		// 
			CheckButtonPressed(AcceptButton,CancelButton, Display1, ProgramSelect1, ProgramSelect2, ProgramSelect3, Door1, Buzz);
		}
}

/**
 **************************************************************************************
 * Function definitions                               
 **************************************************************************************
 **/

// Initialise the door with the corresponding port
// Arguments: none
// Returns: void
Door::Door()
{
	port_map = DOOR_OPEN_CLOSE;
}

// Check to see if the door is open or closed
// Arguments: none
// Returns: 0 if closed, 1 if open
int Door::ReadDoorPort()
{
	port_value = (DOOR_OPEN_CLOSE_PORT) & port_map;
	return port_value;
}

// Initialise the motor with the corresponding port
// Arguments: none
// Returns: void
Motor::Motor()
{
	port_map = MOTOR_CONTROL;
}

// Set the motor to rotate in the chosen direction
// and start rotating
// Arguments: CLOCKWISE or ANTICLOCKWISE
// Returns: void
void Motor::Rotate(bool direction)
{
	if (direction == CLOCKWISE)
	{
		MOTOR_DIRECTION_PORT &= ~(uint16_t) MOTOR_DIRECTION;  // Set motor direction to clockwise
		MOTOR_CONTROL_PORT |= (uint16_t) MOTOR_CONTROL;   // Turn motor on
	}
	else
	{
		MOTOR_DIRECTION_PORT |= (uint16_t) MOTOR_DIRECTION;  // Set motor direction to anticlockwise
		MOTOR_CONTROL_PORT |= (uint16_t) MOTOR_CONTROL;   // Turn motor on
	}
}

// Stop the motor
// Arguments: none
// Returns: void
void Motor::Stop()
{
	MOTOR_CONTROL_PORT &= ~(uint16_t) MOTOR_CONTROL;  // Turn motor off
}

// Initialise the button with the chosen port
// corresponding to the button type
// Arguments: button type (i.e accept, cancel...)
// Returns: void
Button::Button(uint16_t port)
{
	port_map = port;
}

// Check whether the button is on or off
// Arguments: none
// Returns: button state (1 = on, 0 = off)
bool Button::GetButtonState()
{
	return (GPIOE->IDR) & port_map;
}

// Display the chosen digit on the
// 7 segment display
// Arguments: digit to be displayed
// Returns: void
void Display::UpdateDisplay(uint16_t digit)
{
	DISPLAY_PORT |= (uint16_t) digit; 
}

// Convert the number to be shown on the
// display to the corresponding combination
// of segments A, B, C and D
// Arguments: number to be converted and displayed
// Returns: void
void Display::DisplayNumber(int number)
{
	// clear the previous display
	DISPLAY_PORT &= ~((uint16_t) (DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D));
	// Initialise the decoded_number to 0x0000
	uint16_t decoded_number = 0x0000; 
		if (number < 10)
		{
			if (number >= 8) // Check whether to set MSB to 1
				{
				decoded_number |= DISPLAY_D; 
				number -= 8;
				}
			if (number >= 4) // Check whether to set second MSB to 1
				{
				decoded_number |= DISPLAY_C;
				number -= 4;
				}
			if (number >= 2) // Check whether to set 3rd MSB to 1
				{
				decoded_number |= DISPLAY_B;
				number -= 2;
				}
			if (number >= 1) // Check whether to set LSB to 1
				{
				decoded_number |= DISPLAY_A;
				number -= 1;
				}
		}
		else
		{
				// not a valid number - clear the display
				decoded_number |= DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D;
		}
		// write the decoded number to the display
		UpdateDisplay(decoded_number);
}

// Sound the buzzer for a short time
// Arguments: none
// Returns: void
void Buzzer::SoundBuzzer()
{
		BUZZER_PORT ^= (uint16_t) 0x0040;   // toggle buzzer on
		Timer().Delay(DELAY/2);
		BUZZER_PORT ^= (uint16_t) 0x0040;   // toggle buzzer off after short time
		Timer().Delay(DELAY/2);
}

// Return the time elapsed since the timer was initialised
// Arguments: none
// Returns: time passed since timer started
int Timer::GetTimeCount()
{
	return time_count;
}

// Set the timer to count in seconds
// Arguments: time in s
// Returns: void
void Timer::SetTimeCount(int time)
{
	time_count = time*1000;
}


// Delay for a time given in ms using appropriate millisecond delay function
// Arguments: time in ms
// Returns: void
void Timer::Delay(uint16_t time){
	DELAYER(time);
	time_count-=time;
}

// Initialise the program according to the user input
// Arguments: program number
// Returns: void
/*WM_Program::WM_Program(int prog_num)
{
	switch(prog_num)
		case(0) :
			char Cycle[][2] = {{'fill', 5}, {'heat', 2}, {'wash_slow', 3}, {'empty', 4}, {'fill', 4}, {'rinse_slow', 4}, {"empty", 3}, {"spin_high", 6}, {"dry", 5}, {"complete", 0}};
}*/

// Check if any of the buttons have been pressed
// Each button being pressed corresponds to a number on the display
// Pressing the accept button displays 2, cancel button displays 3 and so on
// Arguments: all of the buttons to be checked on the washing machine board
// Returns: void
void CheckButtonPressed(Button AcceptButton, Button CancelButton, Display Display1, Button ProgramSelect1, Button ProgramSelect2, Button ProgramSelect3, Door Door1, Buzzer Buzz){
	if (AcceptButton.GetButtonState())
		{
			Display1.DisplayNumber(2);
		}
		else if (CancelButton.GetButtonState())
		{
			Display1.DisplayNumber(3);
		}
		else if (ProgramSelect1.GetButtonState())
		{
			Display1.DisplayNumber(6);
		}
		else if (ProgramSelect2.GetButtonState())
		{
			Display1.DisplayNumber(5);
		}
		else if (ProgramSelect3.GetButtonState())
		{
			Display1.DisplayNumber(4);
		}
		else
		{
			if (Door1.ReadDoorPort()){
				Display1.DisplayNumber(0);
				Buzz.SoundBuzzer();
			}
			else{
				Display1.DisplayNumber(1);
			}	
		}
}
