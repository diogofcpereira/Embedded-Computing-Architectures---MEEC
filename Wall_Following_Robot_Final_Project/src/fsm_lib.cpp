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

void WALL_calc_outputs(fsm_t &WALL, int front_distance, int right_distance, int left_distance)
{
    if(WALL.state == START)
    {
        digitalWrite(LED_INTERNAL, HIGH);
        if(front_distance < right_distance && front_distance < left_distance)
        {
            if(front_distance > 60)
            {    
                forward_fast();
            }
            else if(front_distance < 60 && front_distance > 20)
            {
                forward_slow();
            }
            if(front_distance <= 20)
            {
                spin_right();
            }
        }
        else if(right_distance < front_distance && right_distance < left_distance)
        {
            spin_right();
        }
        else if(left_distance < front_distance && left_distance < right_distance)
        {
            spin_left();
        }
        else
        {
            forward_fast();
        }
    }
    else if(WALL.state == ADJUST_LEFT)
    {
        if(front_distance > 20)
        {
            if(left_distance >= 15 && left_distance <= 18)
            {
                forward_slow();
            } 
            else if(left_distance < 15)
            {
                adjust_right();
            }    
            else if(left_distance > 18)
            {
                adjust_left();
            }
        }
        else
        {
            turn_right();
        }
        digitalWrite(LED_INTERNAL, LOW);
    }

    else if(WALL.state == ADJUST_RIGHT)
    {
        if(front_distance > 20)
        {
            if(right_distance >= 15 && right_distance <= 18)
            {
                forward_slow();
            } 
            else if(right_distance < 15)
            {
                adjust_left();
            }    
            else if(right_distance > 18)
            {
                adjust_right();
            }
        }
        else
        {
            turn_left();
        }
        digitalWrite(LED_INTERNAL, LOW);
    }
    else if(WALL.state == FREE_LEFT)
    {
        turn_left();
        digitalWrite(LED_INTERNAL, LOW);
    }
    else if(WALL.state == FREE_RIGHT)
    {
        turn_right();
        digitalWrite(LED_INTERNAL, LOW);
    }
    else if(WALL.state == SPIN)
    {
        spin_right();
        digitalWrite(LED_INTERNAL, LOW);
    }
}

void WALL_calc_next_state(fsm_t &WALL, int front_distance, int left_distance, int right_distance)
{
    if((WALL.state == START) && left_distance <= 20)
    {
        WALL.state_new = ADJUST_LEFT;
    }
    else if((WALL.state == START) && right_distance <= 20)
    {
        WALL.state_new = ADJUST_RIGHT;
    }
    else if((WALL.state == ADJUST_LEFT) && front_distance > 25 && left_distance > 25) 
    {
        WALL.state_new = FREE_LEFT;
    }
    else if((WALL.state == ADJUST_RIGHT) && front_distance > 25 && right_distance > 25)
    {
        WALL.state_new = FREE_RIGHT;
    }
    else if ((WALL.state == FREE_LEFT) && left_distance <= 20)
    {
        WALL.state_new = ADJUST_LEFT;
    }
    else if((WALL.state == FREE_RIGHT) && right_distance <= 20)
    {
        WALL.state_new = ADJUST_RIGHT;
    }
    else if((WALL.state == ADJUST_LEFT || WALL.state == ADJUST_RIGHT || WALL.state == FREE_LEFT || WALL.state == FREE_RIGHT) && front_distance <= 25 && right_distance <= 25 && left_distance <= 25)
    {
        WALL.state_new = SPIN;
    }
    else if((WALL.state == ADJUST_RIGHT) && right_distance > 60)
    {
        WALL.state_new = START;
    }
    else if((WALL.state == ADJUST_LEFT) && left_distance > 60)
    {
        WALL.state_new = START;
    }
    else if((WALL.state == SPIN) && front_distance > 25 && left_distance <= 20)
    {
        WALL.state_new = ADJUST_LEFT;
    }
    else if((WALL.state == SPIN) && front_distance > 25 && right_distance <= 20)
    {
        WALL.state_new = ADJUST_RIGHT;
    }
}