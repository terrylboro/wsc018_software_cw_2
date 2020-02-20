/**
 ******************************************************************************
 * File Name          : WM.cpp
 * Description        : Application to demonstrate interaction with the
 *                      washing machine simulator
 ******************************************************************************
 **/

/* 
  washing machine outputs (ports C and D)
  ---------------------------------------
  0x0040 PC6  Buzzer		
  0x0100 PD8  7 segment display bit A
  0x0400 PD10 7 segment display bit C
  0x0800 PD11 7 segment display bit B
  0x1000 PD12 motor control	
  0x2000 PD13 7 segment display bit D
  0x4000 PD14 reset latches
  0x8000 PD15 motor direction

  washing machine inputs (port E)
  -------------------------------
  0x0100 PE8  programme select 1
  0x0200 PE9  programme select 2
  0x0400 PE10 programme select 3
  0x0800 PE11 door open/close
  0x1000 PE12 accept button
  0x2000 PE13 cancel button
  0x8000 PE15 motor speed feedback
*/

 /*
 * Configuration of the STM32 Discovery board
 */
extern "C" {  // this is needed to make C++ and C work together
  #include "gpio_setup.h"
	#include "port_map.h"
	#include "pin_map.h"
	#include "time.h"
	#include "cmath"
}

// define a delay in milliseconds to be used between the blinking of LEDs
#define DELAY 1000
#define CLOCKWISE 0
#define ANTICLOCKWISE 1

// Make classes for devices
class Door
{
	public:
		Door();
		//void ReadDoorPort(); // read value in port found
		int ReadDoorPort();
	private:
		uint16_t port_map; // port name
		bool port_value; // value of port
};

class Motor
{
	public:
		Motor();
		void Rotate(bool direction);
		void Stop();
	private:
		uint16_t port_map; // port name
		bool direction; // value of port
};

class Button
{
	public:
		Button(uint16_t port);
		bool GetButtonState();
	private:
		uint16_t port_map; // port name
		bool state; // value of port
};

class Display
{
	public:
		void UpdateDisplay(uint16_t digit);
		void DisplayNumber(int number);
	private:
		uint16_t port_map; // port name
		bool port_value; // digit displayed
};

class Buzzer
{
	public:
		void SoundBuzzer();
	private:
		uint16_t port_map;
};

class Timer
{
	public:
		Timer();
		double GetTimePassed();
	private:
		int time_passed;
		time_t prog_start_time;
};

/**
 * Run the application to light LEDs and respond to the
 * USER button press
 */
int main(void) {

  // STM32F3 Discovery Board initialization
  board_setup();
	Door Door1;
	Motor Motor1;
	Display Display1;
	Button AcceptButton(ACCEPT_BUTTON);
	Button CancelButton(CANCEL_BUTTON);
	Button ProgramSelect1(PROG_SEL_1);
	Button ProgramSelect2(PROG_SEL_2);
	Button ProgramSelect3(PROG_SEL_3);
	Buzzer Buzz;
	//Timer Timer;
	
	//double time_elapsed;

	while(1)
	{
		// Check whether door is open
		if (Door1.ReadDoorPort())
		{
		// If open then show zero
		DISPLAY_PORT &= ~(uint16_t) DISPLAY_0;
		Buzz.SoundBuzzer();
		HAL_Delay(DELAY);
		}
		else 
		{
		// If closed show one
		//DISPLAY_PORT &= ~(uint16_t) DISPLAY_0; // clear
		//DISPLAY_PORT |= (uint16_t) DISPLAY_A | DISPLAY_D | DISPLAY_C;
		Display1.DisplayNumber(1);
		HAL_Delay(DELAY);
		};
		
		// Check which button has been pressed
		if (AcceptButton.GetButtonState())
		{
			Display1.DisplayNumber(2);
			HAL_Delay(DELAY);
		}
		else if (CancelButton.GetButtonState())
		{
			Display1.DisplayNumber(3);
			HAL_Delay(DELAY);
		}
		else if (ProgramSelect1.GetButtonState())
		{
			Display1.DisplayNumber(4);
			HAL_Delay(DELAY);
		}
		else if (ProgramSelect2.GetButtonState())
		{
			Display1.DisplayNumber(5);
			HAL_Delay(DELAY);
		}
		else if (ProgramSelect3.GetButtonState())
		{
			Display1.DisplayNumber(6);
			HAL_Delay(DELAY);
		}
		else
		{
			Display1.DisplayNumber(7);
		}
		
		
		
//		//time_elapsed = Timer.GetTimePassed();
//		//if (std::fmod(Timer.GetTimePassed(),10) == 0)
//		if (std::fmod(time_elapsed,10) == 0)
//		{
//			Motor1.Rotate(ANTICLOCKWISE);
//		}
//		else
//		{
//			Motor1.Rotate(CLOCKWISE);
//		};
	};
}

// Initialise the door with the corresponding port
// Arguments: none
// Returns: void
Door::Door()
{
	port_map = DOOR_OPEN_CLOSE;
}

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
			if (number >= 8)
				{
				decoded_number |= DISPLAY_D;
				number -= 8;
				}
			if (number >= 4)
				{
				decoded_number |= DISPLAY_C;
				number -= 4;
				}
			if (number >= 2)
				{
				decoded_number |= DISPLAY_B;
				number -= 2;
				}
			if (number >= 1)
				{
				decoded_number |= DISPLAY_A;
				number -= 1;
				}
		}
		else
		{
				// not a valid number - clear it the display
				decoded_number |= DISPLAY_A | DISPLAY_B | DISPLAY_C | DISPLAY_D;
		}
		// write the decoded number to the display
		UpdateDisplay(decoded_number);
}

// Sound the buzzer
// Arguments: none
// Returns: void
void Buzzer::SoundBuzzer()
{
		BUZZER_PORT ^= (uint16_t) 0x0040;   // toggle buzzer on
		HAL_Delay(DELAY/2);
		BUZZER_PORT ^= (uint16_t) 0x0040;   // toggle buzzer off after short time
		HAL_Delay(DELAY/2);
}

// Initialise the timer
// Arguments: none
// Returns: void
Timer::Timer()
{
	prog_start_time = time(&prog_start_time);
}

// Return the time elapsed since the timer was initialised
// Arguments: none
// Returns: time passed since timer started
double Timer::GetTimePassed()
{
	time_t current_time;
	time_passed = difftime(current_time, prog_start_time);
	return time_passed;
}
