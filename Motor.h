#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

void Init_MOTOR(char Motor_Pin);    //Initialize Motor Pin.

void controlFanSpeed(float temperature,char Motor_Pin,int* Fan); // Function to control the fan speed

#endif