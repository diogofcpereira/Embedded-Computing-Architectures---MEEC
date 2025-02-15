#ifndef MOVEMENT_LIB
#define MOVEMENT_LIB

#include <Arduino.h>
#include "defines.hpp"

void stop();
void forward_fast();
void forward_slow();
void adjust_left();
void adjust_right();
void turn_left();
void turn_right();
void spin_right();
void spin_left();

#endif