#include <IR_Seeker.h>
#include <Defender_Motor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_LiquidCrystal.h>

#define IRSEEKER 0x08

Adafruit_BNO055 bno;
Adafruit_LiquidCrystal lcd(0);

Motors motors;
IR_Seeker seeker;

//Line Tracking
uint8_t irOutputPins[4] = {0, 0, 0, 0};
int lineValues[4] = {0};

void readLineValues() {
  for(int x = 0; x < 4; x++) {
    lineValues[x] = digitalRead(irOutputPins[x]);
  }
}

//IMU
double xOrientation = 0;
double yOrientation = 0;
double zOrientation = 0;

void updateOrientation() {
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

  xOrientation = orientationData.acceleration.x;
  yOrientation = orientationData.acceleration.y;
  zOrientation = orientationData.acceleration.z;
  
  Serial.print("x: ");
  Serial.print(xOrientation);
  Serial.print(" y: ");
  Serial.print(yOrientation);
  Serial.print(" z: ");
  Serial.println(zOrientation);
}

//LCD
void updateStatus(String robotStatus) {
  Serial.println(robotStatus);
  lcd.setCursor(0, 0);
  lcd.print(robotStatus);
  lcd.print("                ");
}

void updateDetail(String robotDetail) {
  Serial.println(robotDetail);
  lcd.setCursor(0, 1);
  lcd.print(robotDetail);
  lcd.print("                ");
}

//Movement Logic (Defending)

//Moves the robot
//towards the ball
void checkBall() {
//  readSeekerValues();
//  switch(getBallDirection()) {
//    //move left to the ball
//    case 3:
//    case 4:
//      rightMotorSpeed += 5;
//      leftMotorSpeed += 5;
//      break;
//    //turn left
//    case 1:
//    case 2:
//      rightMotorSpeed += 5;
//      leftMotorSpeed -= 5;
//      break;
//    case 5:
//      //approach the ball or something
//      rightMotorSpeed += 5;
//      leftMotorSpeed += 5;
//      break;
//    //move right to the ball
//    case 6:
//    case 7:
//      rightMotorSpeed += 5;
//      leftMotorSpeed += 5;
//    case 8:
//    case 9:
//      //turn right
//      rightMotorSpeed -= 5;
//      leftMotorSpeed += 5;
//      break;
//  }
}

//Makes sure the robot
//Doesn't run into the
//goal zone

//Should keep the line
//in between the 4
//light sensors
void checkLine() {
//  readLineValues();

//  if(lineValues[0] == 1) {
//    leftMotorSpeed += 15;
//    //left motor forward
//  }
//  if(lineValues[1] == 1) {
//    leftMotorSpeed -= 15;
//    //left motor backward
//  }
//  if(lineValues[2] == 1) {
//    rightMotorSpeed += 15;
//    //right motor forward
//  }
//  if(lineValues[3] == 1) {
//    rightMotorSpeed -= 15;
//    //right motor backward
//  }
}

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  bno = Adafruit_BNO055(55, 0x28);
  if(!bno.begin()) {
    while(1);
  }

  seeker = IR_Seeker(IRSEEKER);
  motors = Motors();

  for(int x = 0; x < 4; x++) {
    pinMode(irOutputPins[x], INPUT);
  }
  
  delay(500);
  motors.leftMotorSpeed = 255;
  motors.rightMotorSpeed = 255;
  motors.middleMotorSpeed = 255;
}

void loop() {
  updateOrientation();
  updateDetail(String(xOrientation));
  seeker.readValues();
//  
//  checkBall();
//  checkLine();
  motors.updateMotorSpeeds();
}
