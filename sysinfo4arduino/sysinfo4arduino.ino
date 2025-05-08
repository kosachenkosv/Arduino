// SysInfo for Arduino
#define Version 1.02

#include <avr/boot.h>

void setup()
{
  Serial.begin(9600);

  Serial.print("SysInfo for Arduino version ");
  Serial.println(Version);
  Serial.println();

  VCC();
  Frequency();
  Fuses();
  TestPins();
}

void loop() {}

void VCC()
{
  #define Vref 1100
  int mvVcc;

  ADMUX = 1<<REFS0 | 0x0E;
  ADCSRA = (1<<ADEN) | (1<<ADATE) | (1<<ADSC) | 5;
  delay(1);
  mvVcc = (1023L * Vref) / ADC;

  Serial.print("VCC = ");
  Serial.print(mvVcc);
  Serial.println(" mV");
  Serial.println();
}

void Frequency()
{
  unsigned long ustime1, ustime2;
  int i, mhzFreq, iMax = 10000;

  Serial.print("F_CPU = ");
  Serial.println(F_CPU);

  ustime1 = micros();
  for(i=iMax; i>0; i--) __asm__("nop\n\t");
  ustime2 = micros();
  mhzFreq = 5 * (long)iMax / (ustime2 - ustime1) + 1;

  Serial.print("Frequency = ");
  Serial.print(mhzFreq);
  Serial.println(" MHz");
  Serial.println();
}

void Fuses()
{
  #define SIGRD 5

  Serial.print("Signatura = ");
  Serial.print(boot_signature_byte_get(0),HEX);
  Serial.print(boot_signature_byte_get(2),HEX);
  Serial.println(boot_signature_byte_get(4),HEX);

  Serial.print("Fuses (L/H/ext) = ");
  Serial.print(boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS),HEX);
  Serial.print(boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS),HEX);
  Serial.println(boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS),HEX);

  Serial.println();
}

void TestPins()
{
  #define FIRST_PIN 0
  #define LAST_PIN 19

  Serial.println("Test of short circuit on GND or VCC:");

  for(byte pin = FIRST_PIN; pin <= LAST_PIN; pin++)
  {
    if(pin < 10) Serial.print("Pin:  ");
    else Serial.print("Pin: ");
    Serial.print(pin);

    pinMode(pin, OUTPUT);
    digitalWrite(pin, 0);
    Serial.print("    Low: ");
    if(!digitalRead(pin)) Serial.print("Ok  ");
    else Serial.print("Fail");

    digitalWrite(pin, 1);
    Serial.print("  High: ");
    if(digitalRead(pin)) Serial.print("Ok  ");
    else Serial.print("Fail");

    pinMode(pin, INPUT_PULLUP);
    Serial.print("  Pull Up: ");
    if(digitalRead(pin)) Serial.print("Ok  ");
    else Serial.print("Fail");

    Serial.println();
    pinMode(pin, INPUT);
  }
 
  Serial.println();
}
