#ifndef Defender_Motor_h
#define Defender_Motor_h

#include <Adafruit_MotorShield.h>

#define LM 1
#define RM 2
#define MM 3

class Motors {
	public:
		Motors();
		void updateMotorSpeeds();
		int leftMotorSpeed;
		int rightMotorSpeed;
		int middleMotorSpeed;
	private:
		Adafruit_MotorShield ms;
		Adafruit_DCMotor *_leftMotor;
		Adafruit_DCMotor *_rightMotor;
		Adafruit_DCMotor *_middleMotor;
};

#endif