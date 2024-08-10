#include "Motor.h"

#define IDEAL_TEMP 25.0

void Init_MOTOR(char Motor_Pin)
{
pinMode(Motor_Pin, OUTPUT);
}

// Function to control the fan speed
void controlFanSpeed(float temperature,char Motor_Pin,int* Fan)
{
  // Calculate the fan speed based on the temperature difference
  float tempDiff = temperature - IDEAL_TEMP;
  // int fanSpeed = map(abs(tempDiff), 0, 10, 0, 255); // 0 to 100% speed
     *Fan = map(abs(tempDiff), 0, 10, 0, 255);
  // Set the motor speed
    analogWrite(Motor_Pin, *Fan);
  
    /*Serial.print("Fan Speed: ");
    //Serial.print((analogRead(Motor_PIN) * 100.0) / 255.0);
    Serial.print(fanSpeed);
    Serial.println("%");*/
}