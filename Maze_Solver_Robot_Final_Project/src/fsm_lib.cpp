#include "fsm_lib.hpp"
#include <Arduino.h>
#include "defines.hpp"
#include "movement_lib.hpp"

void set_state(fsm_t &fsm, int state_new)
{
    if(fsm.state != state_new)
    {
        fsm.state = state_new;
        fsm.tis = 0;
        fsm.tes = millis();
    }
}

void MOV_calc_next_state(fsm_t &MOV, fsm_t &WALL, int front_distance, int left_distance, int right_distance)
{
    if((MOV.state == STOP || MOV.state == MOVE_LEFT || MOV.state == MOVE_RIGHT || MOV.state == TURN_LEFT || MOV.state == TURN_RIGHT || MOV.state == ROTATION) && (WALL.state == MOVE_FORWARD))
    {
        MOV.state_new = MOVE_FRONT;
    }   
    else if((MOV.state == STOP || MOV.state == MOVE_FRONT || MOV.state == MOVE_RIGHT || MOV.state == TURN_LEFT || MOV.state == TURN_RIGHT || MOV.state == ROTATION) && (WALL.state == ADJUST_LEFT))
    {
        MOV.state_new = MOVE_LEFT;
    }
    else if((MOV.state == STOP || MOV.state == MOVE_LEFT || MOV.state == MOVE_FRONT || MOV.state == TURN_LEFT || MOV.state == TURN_RIGHT || MOV.state == ROTATION) && (WALL.state == ADJUST_RIGHT))
    {
        MOV.state_new = MOVE_RIGHT;
    }
    else if((MOV.state == STOP || MOV.state == MOVE_LEFT || MOV.state == MOVE_FRONT || MOV.state == MOVE_RIGHT || MOV.state == TURN_RIGHT || MOV.state == ROTATION) && (WALL.state == FREE_LEFT))
    {
        MOV.state_new = TURN_LEFT;
    }
    else if((MOV.state == STOP || MOV.state == MOVE_LEFT || MOV.state == MOVE_FRONT || MOV.state == MOVE_RIGHT || MOV.state == TURN_LEFT || MOV.state == ROTATION) && (WALL.state == FREE_RIGHT))
    {
        MOV.state_new = TURN_RIGHT;
    }
    else if((MOV.state == STOP || MOV.state == MOVE_LEFT || MOV.state == MOVE_FRONT || MOV.state == MOVE_RIGHT || MOV.state == TURN_LEFT || MOV.state == TURN_RIGHT) && (WALL.state == SPIN))
    {
        MOV.state_new = ROTATION;
    }
}

void MOV_calc_outputs(fsm_t &MOV, int front_distance, int right_distance, int left_distance)
{
    if(MOV.state == STOP)
    {
        stop();
    }
    else if(MOV.state == MOVE_FRONT)
    {
        if(front_distance > 40)
        {
            forward_fast();
        }

        else if(front_distance <= 40)
        {
            forward_slow();
        }
    }
    else if(MOV.state == MOVE_LEFT)
    {
        if(left_distance <= 23 && left_distance >= 22)
        {
            //forward_slow();
            forward_fast();
        } 
        else if(left_distance > 23)
        {
            adjust_left();
        }    
        else if(left_distance < 22)
        {
            adjust_right();
        }
    }
    else if(MOV.state == MOVE_RIGHT)
    {
        if(right_distance <= 23 && right_distance >= 22)
        {
            //forward_slow();
            forward_fast();
        }
        else if(right_distance > 23)
        {   
            adjust_right();
        }
        else if(right_distance < 22)
        {
            adjust_left();
        }
    }
    else if(MOV.state == TURN_LEFT)
    {
        spin_left();
    }
    else if(MOV.state == TURN_RIGHT)
    {
        spin_right();
    }
    else if(MOV.state == ROTATION)
    {
        spin_right();
    }
}

void WALL_calc_next_state(fsm_t &WALL, int front_distance, int left_distance, int right_distance)
{
    if((WALL.state == START) && front_distance > 25 && right_distance > 25 && left_distance > 25)
    {
        WALL.state_new = MOVE_FORWARD;        
    }
    else if((WALL.state == START || WALL.state == MOVE_FORWARD || WALL.state == ADJUST_RIGHT) && front_distance > 25 && left_distance <= 25)
    {
        WALL.state_new = ADJUST_LEFT;
    }   
    else if((WALL.state == START || WALL.state == MOVE_FORWARD || WALL.state == ADJUST_LEFT) && front_distance > 25 && right_distance <= 25)
    {
        WALL.state_new = ADJUST_RIGHT;
    } 
    else if((WALL.state == ADJUST_LEFT || WALL.state == ADJUST_RIGHT) && front_distance > 25 && right_distance > 35 && left_distance > 35)
    {
        WALL.state_new = MOVE_FORWARD;        
    }
    else if((WALL.state == MOVE_FORWARD || WALL.state == ADJUST_LEFT || WALL.state == ADJUST_RIGHT) && front_distance <= 25 && right_distance <= 25 && left_distance >= 35)
    {
        WALL.state_new = FREE_LEFT;        
    }
    else if((WALL.state == MOVE_FORWARD || WALL.state == ADJUST_LEFT || WALL.state == ADJUST_RIGHT) && front_distance <= 25 && right_distance >= 35 && left_distance <= 25)
    {
        WALL.state_new = FREE_RIGHT;        
    }
    else if((WALL.state == MOVE_FORWARD || WALL.state == ADJUST_LEFT || WALL.state == ADJUST_RIGHT) && front_distance <= 25 && right_distance >= 35 && left_distance >= 35)
    {
        WALL.state_new = FREE_RIGHT;        
    }
    else if((WALL.state == FREE_LEFT || WALL.state == FREE_RIGHT) && front_distance > 25 && right_distance > 25 && left_distance > 25)
    {
        WALL.state_new = MOVE_FORWARD;    
    }
    else if((WALL.state == FREE_LEFT || WALL.state == FREE_RIGHT) && front_distance > 25 && right_distance <= 25 && left_distance > 25)
    {
        WALL.state_new = ADJUST_RIGHT; 
    }
    else if((WALL.state == FREE_LEFT || WALL.state == FREE_RIGHT) && front_distance > 25 && right_distance > 25 && left_distance <= 25)
    {
        WALL.state_new = ADJUST_LEFT;       
    }
    else if((WALL.state == MOVE_FORWARD || WALL.state == ADJUST_LEFT || WALL.state == ADJUST_RIGHT) && front_distance <= 25 && right_distance < 35 && left_distance < 35)
    {
        WALL.state_new = SPIN;
    }
    else if((WALL.state == SPIN) && front_distance > 25 && right_distance > 25 && left_distance > 25)
    {
        WALL.state_new = MOVE_FORWARD;      
    }
    else if((WALL.state == SPIN) && front_distance > 25 && right_distance <= 25 && left_distance > 25)
    {
        WALL.state_new = ADJUST_RIGHT;        
    }
    else if((WALL.state == SPIN) && front_distance > 25 && right_distance > 25 && left_distance <= 25)
    {
        WALL.state_new = ADJUST_LEFT;       
    }
}