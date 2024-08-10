#include <Wire.h>
#include "DHT_LIB.h"
#include "Motor.h"

#define PIN_Data 5
#define Motor_PIN 9

//Initialization for DHT sensor
float Temp = 0;          //decler Temperature
float RH = 0;         //declcer Humidity

int Fan_Speed = 0;

void setup()
{
  // Initialize the UART interface
  Serial.begin(9600);
  //Initialize Pin Data.
  Init_DHT(PIN_Data);
  //Initialize Motor.
  Init_MOTOR(Motor_PIN);
}

void loop() 
{
  
  Read_DHT(5,&Temp,&RH);
  controlFanSpeed(Temp,Motor_PIN,&Fan_Speed);

  delay(3000);

  // Report the temperature, humidity, and fan speed 
   Serial.println("");
    Serial.print("Temperature: ");
    Serial.print(Temp);
    Serial.println("C");
    Serial.print("Humidity: ");
    Serial.println(RH);
    Serial.print("Fan Speed: ");
    Serial.print((Fan_Speed*100.0)/255.0);
    Serial.println("%");

}
