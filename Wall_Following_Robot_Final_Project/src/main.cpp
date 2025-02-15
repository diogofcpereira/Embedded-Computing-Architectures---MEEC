#include <Arduino.h>
#include "pico/cyw43_arch.h"
#include <Wire.h>
#include <VL53L0X.h>
#include "defines.hpp"
#include "fsm_lib.hpp"

VL53L0X sensor_front;
VL53L0X sensor_right;
VL53L0X sensor_left;

float distance_front, prev_distance_front;
float distance_right, prev_distance_right;
float distance_left, prev_distance_left;

unsigned long interval;
unsigned long currentMicros, previousMicros;

fsm_t WALL;

void setup() 
{
    //LED BUILT-IN setup

    pinMode(LED_INTERNAL, OUTPUT);

    interval = 40 * 1000;

    Serial.begin(115200);

    Wire.setSDA(16);
    Wire.setSCL(17);

    Wire.begin();   

    pinMode(XSHUT_Front, OUTPUT);
    digitalWrite(XSHUT_Front, LOW);
    delay(10);
    digitalWrite(XSHUT_Front, HIGH);
    delay(10);

    sensor_front.setTimeout(500);
    while(!sensor_front.init())
    {
        Serial.println(F("Failed to detect and initialize front VL53L0X!"));
        delay(100);
    }
    Serial.println(F("Success initializing front VL530X!"));
    sensor_front.setAddress(ADR_FRONT);


    pinMode(XSHUT_Right, OUTPUT);
    digitalWrite(XSHUT_Right, LOW);
    delay(10);
    digitalWrite(XSHUT_Right, HIGH);
    delay(10);

    sensor_right.setTimeout(500);
    while(!sensor_right.init())
    {
        Serial.println(F("Failed to detect and initialize right VL53L0X!"));
        delay(100);
    }
    Serial.println(F("Success initializing right VL530X!"));
    sensor_right.setAddress(ADR_RIGHT);


    pinMode(XSHUT_Left, OUTPUT);
    digitalWrite(XSHUT_Left, LOW);
    delay(10);
    digitalWrite(XSHUT_Left, HIGH);
    delay(10);

    sensor_left.setTimeout(500);
    while(!sensor_left.init())
    {
        Serial.println(F("Failed to detect and initialize left VL53L0X!"));
        delay(100);
    }
    Serial.println(F("Success initializing left VL530X!"));
    sensor_left.setAddress(ADR_LEFT);


    sensor_front.startReadRangeMillimeters();
    sensor_right.startReadRangeMillimeters();
    sensor_left.startReadRangeMillimeters();

    //Motors setup

    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);
    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);

    //State Machines setup
    set_state(WALL, START);

    delay(3000);
}

void loop() 
{
    currentMicros = micros();
    if(currentMicros - previousMicros >= interval)
    {
        previousMicros = currentMicros;

        /* CODE INSIDE THE LOOP */

        /* READ INPUTS */
        if(sensor_front.readRangeAvailable())
        {
            prev_distance_front = distance_front;
            distance_front = sensor_front.readRangeMillimeters() * 1e-3;
        }
        if(sensor_right.readRangeAvailable())
        {
            prev_distance_right = distance_right;
            distance_right = sensor_right.readRangeMillimeters() * 1e-3;
        }
        if(sensor_left.readRangeAvailable())
        {
            prev_distance_left = distance_left;
            distance_left = sensor_left.readRangeMillimeters() * 1e-3;
        }

        /* INITIALIZE NEW DISTANCE MEASURE */

        sensor_front.startReadRangeMillimeters();
        sensor_right.startReadRangeMillimeters();
        sensor_left.startReadRangeMillimeters();

        /* CALCULATE NEXT STATES */
        WALL_calc_next_state(WALL, distance_front*100, distance_left*100, distance_right*100);

        /* UPDATE STATES */
        set_state(WALL, WALL.state_new);

        /* OUTPUTS FROM THE CURRENT STATES */
        WALL_calc_outputs(WALL, distance_front*100, distance_right*100, distance_left*100);

        /*Serial.print(" Dist_front: ");
        Serial.print(distance_front, 3);
        Serial.println();*/

        /*Serial.print(" Dist_right: ");
        Serial.print(distance_right, 3);
        Serial.println();*/

        /*Serial.print(" Dist_left: ");
        Serial.print(distance_left, 3);
        Serial.println();*/
    }
}

