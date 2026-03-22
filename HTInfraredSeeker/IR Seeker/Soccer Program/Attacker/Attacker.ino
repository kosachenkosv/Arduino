#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_MotorShield.h>
//Motors

#define TL 1
#define TR 2
#define BL 3
#define BR 4

Adafruit_MotorShield motorShield;

Adafruit_DCMotor *topLeftMotor;
Adafruit_DCMotor *topRightMotor;
Adafruit_DCMotor *bottomLeftMotor;
Adafruit_DCMotor *bottomRightMotor;

void setupMotors() {
  motorShield = Adafruit_MotorShield();
  topLeftMotor = motorShield.getMotor(TL);
  topRightMotor = motorShield.getMotor(TR);
  bottomLeftMotor = motorShield.getMotor(BL);
  bottomRightMotor = motorShield.getMotor(BR);
}

//Line Tracking
uint8_t irOutputPins[6] = {0, 0, 0, 0, 0, 0};
int lineValues[6] = {0};

void readLineValues() {
  for(int x = 0; x < 6; x++) {
    lineValues[x] = analogRead(irOutputPins[x]);
  }
}

//i2c
int readi2c(int device, int address) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(device, 1);
  if(1 <= Wire.available())
    return Wire.read();
  return -1;
}

//IR Seeker
int seekerValues[5] = {0};

int readIRSeekerSensor(int sensorNumber) {
  //1 is at 0x4a
  return readi2c(IRSEEKER, 0x5A + sensorNumber);
}

void readSeekerValues() {
  for(int x = 0; x < 4; x++) {
    seekerValues[x] = readIRSeekerSensor(x);
  }
}

int getBallDirection() {
  return readi2c(IRSEEKER, 0x49);
}

//IMU
Adafruit_BNO055 bno;

double xOrientation = 0;
double yOrientation = 0;
double zOrientation = 0;

void setupIMU() {
  bno = Adafruit_BNO055(55, 0x28);
  if(!bno.begin()) {
    while(1);
  }
}

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

void setup() {
  Serial.begin(9600);
  
  setupMotors();
  setupIMU();
}

void loop() {
  // put your main code here, to run repeatedly:

}
