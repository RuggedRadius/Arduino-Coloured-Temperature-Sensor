// Temperature Sensor
// By Ben Royans
// 9/11/2019

#include <dht.h>

dht DHT;

// DEFINITIONS
#define pinDHT11 4
#define pinRed 9
#define pinGreen 11
#define pinBlue 10
#define sensor A2
#define buzzer 5

// USER SETTINGS
const int rangeMin = 0;
const int rangeMax = 40;
const int idealTemperature = 24;

bool ideal;

double humidity;
float temperature;

void setup() {  
  Serial.begin(9600);
  Serial.println("\t\t\t****************************************************************");
  Serial.println("\t\t\t\t\tColoured Humidity / Temperature Sensor\n");
  Serial.println("\t\t\t\t\t\tCode by Ben Royans © 2019");
  Serial.println("\t\t\t****************************************************************\n");
  Serial.println("\tHUMIDITY (%)\t\tTEMPERATURE (℃)\t\t\tCOLOUR VALUES (R, G, B)");
  Serial.println("\t************\t\t****************\t\t************************\n");

  // Startup tone
  Arpeggio(5, 500, 100, 2000, 100);

  // Delay before accessing sensors
  delay(1000);
}

void loop() {
  DHT.read11(pinDHT11);
  humidity = DHT.humidity;
  float sensorValue = analogRead(sensor);
  float voltageOut = (sensorValue * 5000) / 1024;
  temperature = voltageOut / 10;

//  NORMAL LOOP ****************************
  WriteData(humidity, temperature, Amt(temperature));
  ColourCode(humidity, temperature, Amt(temperature));
  delay(1250);  
//  ****************************************

//// TEST LOOP *****************************
//  temperature = 18;
//  for (; temperature < 41; temperature++)
//  {
//      WriteData(humidity, temperature, Amt(temperature));
//      ColourCode(humidity, temperature, Amt(temperature));
//      delay(1000);
//  }
////  **************************************
}

float Amt (float temperature) {  
  float range = rangeMax - rangeMin;
  float adjTemp = temperature - rangeMin;
  float amt = adjTemp / range;
  return amt;
}

void WriteData(double humidity, float temperature, float amt) {
  Serial.print("\t    ");
  Serial.print(humidity, 1);
  Serial.print("%\t\t\t     ");
  
  Serial.print(temperature);
  Serial.print("℃\t\t\t ");
  
  
  Serial.print(amt * 255);
  Serial.print(", \t");
  Serial.print("0.00");
  Serial.print(", \t");
  Serial.println(255 - (amt * 255));
}

void ColourCode(int humidity, float temperature, float amt) {

  int range = rangeMax - rangeMin;
  
  if (IdealCheck(temperature))
  {
    RGB(0, 255, 0);
  }
  else
  {
    RGB(amt * 255, 0, 255 - (amt * 255));
  }  
}

void RGB(int r, int g, int b) {
  analogWrite(pinRed, r);
  analogWrite(pinGreen, g);
  analogWrite(pinBlue, b);  
}

bool IdealCheck(float temperature)
{
  if (temperature == idealTemperature)
  {    
    return true;
  }
  else
  {
    return false;
  }
}

void PrintCurrentColourValues(float amt) {
  Serial.print(amt * 255);
  Serial.print(",\t");
  Serial.print(0);
  Serial.print(",\t");
  Serial.println(255 - (amt * 255));
}

void Arpeggio(int notes, int interval, int timing, int initial, int del)
{
  for (int i = 0; i < notes; i++)
  {
    tone(buzzer, (initial + (interval * i)), timing);
    delay(del);
  }
}
