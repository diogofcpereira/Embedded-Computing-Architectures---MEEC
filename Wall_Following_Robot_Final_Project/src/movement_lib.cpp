#include <Arduino.h>
#include "defines.hpp"
#include "movement_lib.hpp"

void stop()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, MIN_SPEED);
    analogWrite(PWM2, MIN_SPEED);
}

void forward_fast()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, MAX_SPEED);
    analogWrite(PWM2, MAX_SPEED);
}

void forward_slow()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, ADJUST_SPEED);
    analogWrite(PWM2, ADJUST_SPEED);
}

void adjust_left()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, ADJUST_SPEED);
    analogWrite(PWM2, ADJUST_SPEED - 50);
}

void adjust_right()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, ADJUST_SPEED - 50);
    analogWrite(PWM2, ADJUST_SPEED);
}

void spin_right()
{
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, SPIN_SPEED);
    analogWrite(PWM2, SPIN_SPEED);
}

void spin_left()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    analogWrite(PWM1, SPIN_SPEED);
    analogWrite(PWM2, SPIN_SPEED);
}

void turn_right()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, 30);
    analogWrite(PWM2, SPIN_SPEED);
}

void turn_left()
{
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
    analogWrite(PWM1, SPIN_SPEED);
    analogWrite(PWM2, 30);
}