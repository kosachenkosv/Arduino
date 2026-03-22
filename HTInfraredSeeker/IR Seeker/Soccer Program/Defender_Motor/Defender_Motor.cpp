#include "Defender_Motor.h"

Motors::Motors() {
	leftMotorSpeed = 0;
	rightMotorSpeed = 0;
	middleMotorSpeed = 0;
	
	ms = Adafruit_MotorShield();
	
	_leftMotor = ms.getMotor(LM);
	_rightMotor = ms.getMotor(RM);
	_middleMotor = ms.getMotor(MM);
	
	ms.begin();
}

void Motors::updateMotorSpeeds() {
	if(leftMotorSpeed > 0) {
		_leftMotor->setSpeed(leftMotorSpeed);
		_leftMotor->run(FORWARD);
	} else {
		_leftMotor->setSpeed(-leftMotorSpeed);
		_leftMotor->run(BACKWARD);
	}
	
	if(rightMotorSpeed > 0) {
		_rightMotor->setSpeed(rightMotorSpeed);
		_rightMotor->run(FORWARD);
	} else {
		_rightMotor->setSpeed(-rightMotorSpeed);
		_rightMotor->run(BACKWARD);
	}
	if(leftMotorSpeed > 0) {
		_middleMotor->setSpeed(middleMotorSpeed);
		_middleMotor->run(FORWARD);
	} else {
		_middleMotor->setSpeed(-middleMotorSpeed);
		_middleMotor->run(BACKWARD);
	}
}