#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;

int gLedPin = 13;
int gRxPin = 10;
int gTxPin = 11;

int velocity = 0;  //Здесь будет храниться значение скорости
int defaultSpeed = 100; // это число мы будем использовать в логике поворотов
int start = 1;
int turnServo = 90; //число для поворота

SoftwareSerial BTSerial(gRxPin, gTxPin);

void setup() {
  // 38400 - для метода №1, 9600 - для метода №2
//  BTSerial.begin(38400);
  BTSerial.begin(9600);
  Serial.begin(9600);
  delay(500);
  pinMode(gLedPin,OUTPUT);
  myservo.attach(9);
  myservo.write(turnServo);
  delay(15);
}

//void loop() {
//  if (BTSerial.available()) {
//    Serial.write(BTSerial.read());
//  }
//  if (Serial.available()) {
//    BTSerial.write(Serial.read());
//  }
//}

void loop()
{
  
  if (BTSerial.available())    //Если появились новые команды
  {
    if (start==1)
    {
      for(int i=0;i<5;i++)
      {
        digitalWrite(gLedPin,HIGH);
        delay(500);
        digitalWrite(gLedPin,LOW);
        delay(500);
      }
      
      start = 0;
    }   //вызываем функцию управления
    control(); 
  }
  //Здесь можно написать ещё много своего кода
}

void drive(int M1, int M2)
{
  //управление мотором
  }

void control()  // функция управления
{
  
  /*
   * 
You can get the Android application from the Google Play market:

https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&feature=search_result


Forward---------------------F
Back-------------------------B
Left---------------------------L
Right-------------------------R
Forward Left--------------G
Forward Right------------I
Back Left------------------H
Back Right----------------J
Stop-------------------------S
Front Lights On---------W
Front Lights Off---------w (lower case)
Back Lights On---------U
Back Lights Off---------u (lower case)
Speed 0-------------------0
Speed 10-----------------1
Speed 20-----------------2
Speed 30-----------------3
Speed 40-----------------4
Speed 50-----------------5
Speed 60-----------------6
Speed 70-----------------7
Speed 80-----------------8
Speed 90-----------------9
Speed 100---------------q
Everything OFF--------D
   */
  
  char dataIn = BTSerial.read();  //Считаем значение пришедшей команды
 
  if (dataIn == 'F')         //Если пришла команда "F"
  {
    Serial.println(dataIn);
    drive(velocity, velocity);   //едем вперёд
  }
 
  else if (dataIn == 'B')    //или если пришла команда "B"
  {
    Serial.println(dataIn);
    drive(-velocity, -velocity); //едем назад
  }
 
  else if (dataIn == 'R')    //или если пришла команда "L"
  {
    Serial.println(dataIn);
    drive(-velocity, velocity);  //поворачиваем налево на месте
    turnServo-=2; 
    if (turnServo < 0) turnServo = 0;
    myservo.write(turnServo);
    delay(15);
  }
 
  else if (dataIn == 'L')    //или если пришла команда "R"
  {
    Serial.println(dataIn);
    drive(velocity, -velocity);  //поворачиваем направо на месте
    turnServo+=2; 
    if (turnServo > 180) turnServo = 180;
    myservo.write(turnServo);
    delay(15);
  }
 
  else if (dataIn == 'G')    //или если пришла команда "I", едем вперёд и направо
  {
    Serial.println(dataIn);
    drive(defaultSpeed+velocity, defaultSpeed-velocity);
  }
 
  else if (dataIn == 'H')    //или если пришла команда "J", едем назад и направо
  {
    Serial.println(dataIn);
    drive(-defaultSpeed-velocity, -defaultSpeed+velocity);
  }
 
  else if (dataIn == 'I')   //или если пришла команда "I", едем вперёд и налево
  {
    Serial.println(dataIn);
    drive(defaultSpeed-velocity, defaultSpeed+velocity);
  }
 
  else if (dataIn == 'J')   //или если пришла команда "H", едем назад и налево
  {
    Serial.println(dataIn);
    drive(-defaultSpeed+velocity, -defaultSpeed-velocity);
  }
 
  else if (dataIn == 'S')   //или если пришла команда "S", стоим
  {
    Serial.println(dataIn);
    drive(0, 0);
  }
 
  else if (dataIn == 'U')   //или если "U", зажигаем "передние фары"
  {
        digitalWrite(gLedPin,HIGH);
        Serial.println(dataIn);
  }
  else if (dataIn == 'u')   //или если "u", гасим "передние фары"
  {
        digitalWrite(gLedPin,LOW);
        Serial.println(dataIn);
  }
  else if (dataIn == 'W')   //или если "W", зажигаем "задние фары"
  {
        digitalWrite(gLedPin,HIGH);
        Serial.println(dataIn);
  }
  else if (dataIn == 'w')   ////или если "w", гасим "задние фары"
  {
        digitalWrite(gLedPin,LOW);
        Serial.println(dataIn);
  }
 
  // если к нам пришло значение от 0 до 9
  else if (((dataIn - '0') >= 0) && ((dataIn - '0') <= 9))
  { 
    velocity = (dataIn - '0') * 25; //сохраняем новое значение скорости
    Serial.println(dataIn);
    Serial.print(" Speed ");
    Serial.println(velocity);
  }
 
  else if (dataIn == 'q') //если "q" - полный газ!
  {
    velocity = 255;
    Serial.println(dataIn);
    Serial.print(" Speed ");
    Serial.println(velocity);
  }
}
