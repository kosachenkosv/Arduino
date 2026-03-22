/*
 * Подключение HiTechnic IRSeeker к Arduino
 * (c) Serg Kosachenko
 * Подключение к разъему NXT -> Arduino
   white -> battery Vin (Важно для датчика подать напряжение 3,3-5 Вольт!)
   black -> (GND)
   red -> battery – (GND) 
   green -> Arduino +3.3V 
   yellow -> Arduino SCL (A5)
   blue -> Arduino SDA (A4)
   
 * ToDo:
 * 
 * Программировал R:ED ONE на Arduino IDE 1.8.19
 * 
 * Настройки:
 * Плата: Arduino NANO
 * Процесор: ATmega328P (Old Bootloader)
 * 
 */


#include <Wire.h> //Include the Wire Library
#include <HTInfraredSeeker.h> //Include the IR Seeker Library

//setup runs once at the beginning
void setup() {
  Serial.begin(9600); //Starts the Serial Monitor so we can read output
  Serial.println("Dir\tStrength"); //Prints Dir & Strength at top
  InfraredSeeker::Initialize(); //initializes the IR sensor
}

//loop runs repeatedly
void loop() {   
  //Read the AC (pulsed) information from the IR Sensor
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  
  Serial.print(InfraredBall.Direction); //Print the Direction Number
  Serial.print("\t"); //Print a tab
  Serial.print(InfraredBall.Strength); //Print the Strength Number
  Serial.println(" ;"); //Print a new line
  delay(100); //delay a tenth of a second
}
