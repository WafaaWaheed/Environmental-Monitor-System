#include "DHT_LIB.h"

// Sampling periods
#define temperatureSampPeriod 100 // 100ms
#define humiditySampPeriod 200// 200ms

void Init_DHT(char Pin)
{
pinMode(Pin, INPUT);
digitalWrite(Pin, HIGH);
}

char Read_DHT(char Pin ,float* Temp, float* RH) 
{
  static unsigned long lastTemperatureTime = 0;
  static unsigned long lastHumidityTime = 0;
  
  //Start communication process of DHT Sensor from data sheet

  char data[40]={};          //compelete data transmistion 40 bit
  
  //Start Response
  pinMode(Pin,OUTPUT);
  digitalWrite(Pin,LOW);
  delay(18);
  //Pull up waiting for respone
  digitalWrite(Pin,HIGH);
  pinMode(Pin,INPUT);

  delayMicroseconds(40);   //wait for response

  //Checking response
  if(digitalRead(Pin)==HIGH)
  {
    Serial.println("NOT RESPONDING!"); 
    return 1;
  }

 while (digitalRead (Pin)==LOW){;}     //Wait 80us
 while (digitalRead(Pin)==HIGH){;}     //Wait 80us
  //Communication process is done.

 //Start to read data
 for (int i=0;i<40;i++)
  {
    while (digitalRead(Pin)==LOW){;}        //waiting time (50us) for every bit
    delayMicroseconds(30);
    if(digitalRead(Pin)==HIGH)
    {
      data[i]=1;
      while (digitalRead(Pin)==HIGH){;}        //wait to finish sending 1
    }
  }
  
  // Read temperature every 100ms
  if (millis() - lastTemperatureTime >= temperatureSampPeriod) {
  //data of int temperature 
  int temp_int=0; 
  for (int i=16 ; i<24 ;i++)
  {
    temp_int= temp_int << 1;
    if(data[i]==1) 
    {
      temp_int |=1;
    }
  }
  //data of decimal temperature 
  int temp_deci=0; 
  for (int i=24 ; i<32 ;i++)
  {
    temp_deci= temp_deci << 1;
    if(data[i]==1)
    {
      temp_deci |=1;
    }
  }

  // Read humidity every 200ms
  if (millis() - lastHumidityTime >= humiditySampPeriod) {
  //data of int humidity 
  int rh_int=0; 
  for (int i=0 ; i<8 ;i++)
  {
    rh_int= rh_int << 1;
    if(data[i]==1) 
    {
      rh_int |=1;
    }
  }

  //data of decimal humidity 
  int rh_deci=0; 
  for (int i=8 ; i<16 ;i++)
  {
    rh_deci= rh_deci << 1;
    if(data[i]==1)
    {
      rh_deci |=1;
    }
  }
  
  //data of sum bit
  int sum_check=0;
  for (int i=32 ; i<40 ;i++)
  {
    sum_check= sum_check << 1;
    if(data[i]==1)
    {
      sum_check |=1;
    }
  }

//check the sum_check return 2 if faild
if(sum_check!=(temp_deci+temp_int+rh_deci+rh_int))
{
  Serial.print(F("sum check failed!"));
  return 2;
}

//convert from binary to decimal (float) and store them in pointeer
*RH=rh_deci+rh_int;
*Temp=temp_deci+temp_int;

  lastHumidityTime = millis();
  }

  lastTemperatureTime = millis();
  }
}