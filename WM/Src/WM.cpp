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
		void ReadDoorPort(); // read value in port found
	private:
		uint16_t port_map; // port name
		bool port_value; // value of port
};

class Motor
{
	public:
		Motor();
		void Rotate(bool direction);
	private:
		uint16_t port_map; // port name
		bool direction; // value of port
};


/**
 * Run the application to light LEDs and respond to the
 * USER button press
 */
int main(void) {

  // STM32F3 Discovery Board initialization
  board_setup();
	Door Door;
	Motor Motor;
	while(1)
	{
		Door.ReadDoorPort();
		Motor.Rotate(CLOCKWISE);
	};
	//port_value = (GPIOE->IDR) & port_map;
//	bool port_value = (GPIOE->IDR) & 0x0800;
//	while(1)
//	{
//	if (port_value)
//	{
//		// If open then show blank
//		GPIOD->ODR |= (uint16_t) PD8_DISPLAY_A;
//	}
//	else 
//	{
//		// If closed show zero
//		GPIOD->ODR &= ~(uint16_t) (PD8_DISPLAY_A & PD10_DISPLAY_C & PD11_DISPLAY_B & PD13_DISPLAY_D);
//	}
//}
	
//// hold a bit value returned from a port
//  bool port;
//	
//  // try out each washing machine device in turn
//  GPIOE->ODR ^= (uint16_t) 0x0040;   // toggle PC6 buzzer
//  HAL_Delay(DELAY); 
//  GPIOD->ODR |= (uint16_t) 0x1000;   // PD12 motor control - on
//  HAL_Delay(DELAY); 		
//  GPIOD->ODR &= ~(uint16_t) 0x8000;  // PD15 motor direction - clockwise
//  HAL_Delay(DELAY); 		
//  GPIOD->ODR |= (uint16_t) 0x8000;   // PD15 motor direction - anticlockwise
//  HAL_Delay(DELAY); 
//  GPIOD->ODR &= ~(uint16_t) 0x1000;  // PD12 motor control - off 
//  HAL_Delay(DELAY); 	
//		
//  GPIOD->ODR &= ~(uint16_t) 0x2D00;  // PD8 & PD11 & PD10 & PD13 - turn off all 7 segments of display (shows 0)
//  HAL_Delay(DELAY); 
//  GPIOD->ODR |= (uint16_t) 0x2000;   // PD13 turn on bit D MSB
//  HAL_Delay(DELAY); 		
//  GPIOD->ODR |= (uint16_t) 0x0400;   // PD10 turn on bit C	
//  HAL_Delay(DELAY); 
//  GPIOD->ODR |= (uint16_t) 0x0800;   // PD11 turn on bit B
//  HAL_Delay(DELAY); 		
//  GPIOD->ODR |= (uint16_t) 0x0100;   // PD8 turn on bit A LSB (all outputs 1 - shows blank)
//  HAL_Delay(DELAY); 

//GPIOD->ODR &= ~(uint16_t) 0x2D00;  // turn off all 7 segments of display (shows 0)
//  HAL_Delay(DELAY); 
//		
//  GPIOD->ODR |= (uint16_t) 0x4000;  // PD14 reset input latches
//  HAL_Delay(DELAY); 
//  port = (GPIOE->IDR) & 0x0100 ;     // PE8  programme select 1 (rightmost)
//  if (port) GPIOD->ODR |= (uint16_t) 0x0100; else GPIOD->ODR &= ~(uint16_t) 0x2D00;
//  HAL_Delay(DELAY); 
//  port = (GPIOE->IDR) & 0x0200 ;     // PE9  programme select 2 (middle)
//  if (port) GPIOD->ODR |= (uint16_t) 0x0100; else GPIOD->ODR &= ~(uint16_t) 0x2D00;
//  HAL_Delay(DELAY); 
//  port = (GPIOE->IDR) & 0x0400 ;     // PE10 programme select 3 (leftmost)
//  if (port) GPIOD->ODR |= (uint16_t) 0x0100; else GPIOD->ODR &= ~(uint16_t) 0x2D00;
//  HAL_Delay(DELAY); 
//  port = (GPIOE->IDR) & 0x0800 ;     // PE11 door open/close	
//  if (port) GPIOD->ODR |= (uint16_t) 0x0100; else GPIOD->ODR &= ~(uint16_t) 0x2D00;
//  HAL_Delay(DELAY); 
//  port = (GPIOE->IDR) & 0x1000 ;     // PE12 accept button		
//  if (port) GPIOD->ODR |= (uint16_t) 0x0100; else GPIOD->ODR &= ~(uint16_t) 0x2D00;
//  HAL_Delay(DELAY); 
//  port = (GPIOE->IDR) & 0x2000 ;     // PE13 cancel button			
//  if (port) GPIOD->ODR |= (uint16_t) 0x0100; else GPIOD->ODR &= ~(uint16_t) 0x2D00;
//  HAL_Delay(DELAY); 	
//  port = (GPIOE->IDR) & 0x8000 ;     // PE15 motor speed feedback	
//  HAL_Delay(DELAY); 	
//  GPIOD->ODR &= ~(uint16_t) 0x4000;  // PD14 LOW reset switches
//  HAL_Delay(DELAY); 

//  // Only run the motor if the door is closed
//  GPIOD->ODR &= ~(uint16_t) 0x8000;  // PD15 motor direction - set to clockwise
//  while(1) {
//    port = (GPIOE->IDR) & 0x0800 ;   // PE11 check if door open or closed	
//    if (port) {
//      GPIOD->ODR |= (uint16_t) 0x1000;   // PD12 motor control - on 
//    }
//    else {
//      GPIOD->ODR &= ~(uint16_t) 0x1000;  // PD12 motor control - off 
//    }
//  }

}

Door::Door()
{
	port_map = PE11_DOOR_OPEN_CLOSE;
}

void Door::ReadDoorPort()
{
	port_value = (GPIOE->IDR) & port_map;
	if (port_value)
	{
		// If open then show zero
		GPIOD->ODR &= ~(uint16_t) DISPLAY_0;
		GPIOC->ODR |= (uint16_t) 0x0040;   // toggle PC6 buzzer
		HAL_Delay(DELAY);
	}
	else 
	{
		// If closed show one
		GPIOD->ODR |= (uint16_t) PD8_DISPLAY_A;
		GPIOC->ODR &= ~(uint16_t) 0x0040;   // toggle PC6 buzzer
		HAL_Delay(DELAY);
	}
}

Motor::Motor()
{
	port_map = PD12_MOTOR_CONTROL;
	//GPIOD->ODR |= (uint16_t) 0x1000;   // PD12 motor control - on
}

void Motor::Rotate(bool direction)
{
	if (direction == CLOCKWISE)
	{
		GPIOD->ODR &= ~(uint16_t) 0x8000;  // PD15 motor direction - set to clockwise
		GPIOD->ODR |= (uint16_t) 0x1000;   // PD12 motor control - on 
	}
	else
	{
		GPIOD->ODR |= (uint16_t) 0x8000;  // PD15 motor direction - set to anticlockwise
		GPIOD->ODR |= (uint16_t) 0x1000;   // PD12 motor control - on 
	}
}
