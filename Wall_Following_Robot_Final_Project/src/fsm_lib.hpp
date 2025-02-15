#ifndef FSM_LIB
#define FSM_LIB

#include <Arduino.h>

typedef struct 
{
    int state, state_new;
    unsigned long tes, tis;
} fsm_t;

void set_state(fsm_t &fsm, int state_new);
void WALL_calc_outputs(fsm_t &WALL, int front_distance, int right_distance, int left_distance);
void WALL_calc_next_state(fsm_t &WALL, int front_distance, int left_distance, int right_distance);

#endif
