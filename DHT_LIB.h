#ifndef DHT_H
#define DHT_H

#include <Arduino.h>

void Init_DHT(char Pin);    //Initialize Pin Data.

char Read_DHT(char Pin ,float* Temp, float* RH);      //function to get temperature & humidity and return them by refrance.

#endif