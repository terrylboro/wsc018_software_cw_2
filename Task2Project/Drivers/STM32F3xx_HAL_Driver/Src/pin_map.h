/*
-----------------------------------------
WASHING MACHINE OUTPUTS (PORTS C AND D)
-----------------------------------------
*/

#define BUZZER 0x0040
#define DISPLAY_A 0x0100 // 0001 (LSB)
#define DISPLAY_B 0x0800 // 0010 (3rd MSB)
#define DISPLAY_C 0x0400 // 0100 (2nd MSB)
#define DISPLAY_D 0x2000 // 1000 (MSB)
#define MOTOR_CONTROL 0x1000
#define RESET_LATCHES 0x4000
#define MOTOR_DIRECTION 0x8000
#define DISPLAY_0 0x2D00
/*
---------------------------------------
WASHING MACHINE INPUTS (PORT E)
---------------------------------------
*/

#define PROG_SEL_1 0x0100
#define PROG_SEL_2 0x0200
#define PROG_SEL_3 0x0400
#define DOOR_OPEN_CLOSE 0x0800
#define ACCEPT_BUTTON 0x1000
#define CANCEL_BUTTON 0x2000
#define MOTOR_SPEED_FEEDBACK 0x8000
