/*
-----------------------------------------
WASHING MACHINE OUTPUTS (PORTS C AND D)
-----------------------------------------
*/

#define BUZZER 0x0040
#define DISPLAY_A 0x0100
#define DISPLAY_C 0x0400
#define DISPLAY_B 0x0800 // 3 if after 1 else 2
#define DISPLAY_D 0x2000 // 8 if after 1 else 9
#define MOTOR_CONTROL 0x1000
#define RESET_LATCHES 0x4000
#define MOTOR_DIRECTION 0x8000
#define DISPLAY_0 0x2D00

// 0x2D00 displays blank
// 0x0000 displays 0
// 0x0100 displays 1
// 0x0800 displays 2
// 0x0900 displays 3
// 0x0400 displays 4
// 0x0500 displays 5

// 0x2000 displays 8
// 0x2100 displays 9

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
