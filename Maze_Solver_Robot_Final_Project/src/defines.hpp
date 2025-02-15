#ifndef DEFINES
#define DEFINES

/* DRIVER MOTOR CONTROL PINS */
/* 1 - RIGHT MOTOR */
/* 2 - LEFT MOTOR */
#define DIR1 21
#define DIR2 18
#define PWM1 20
#define PWM2 19

/* SENSOR CONTROL PINS */
#define XSHUT_Front 4
#define XSHUT_Right 5
#define XSHUT_Left 3 

/* ADDRESS SENSORS */
#define ADR_FRONT 0x30
#define ADR_RIGHT 0x32
#define ADR_LEFT 0x34

/* SPEED MODES */
#define MAX_SPEED 160
#define ADJUST_SPEED 100
#define SPIN_SPEED 80
#define MIN_SPEED 0

/* STATES 'MOV' */
#define STOP 0
#define MOVE_FRONT 1
#define MOVE_RIGHT 2
#define MOVE_LEFT 3
#define TURN_RIGHT 4
#define TURN_LEFT 5
#define ROTATION 6

/* STATES 'WALL' */
#define START 0
#define MOVE_FORWARD 1
#define ADJUST_RIGHT 2
#define ADJUST_LEFT 3
#define FREE_RIGHT 4
#define FREE_LEFT 5
#define SPIN 6

/* LED BUILT_IN*/
#define LED_INTERNAL 0

#endif