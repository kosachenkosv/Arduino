#ifndef IR_Seeker_h
#define IR_Seeker_h

#include <Arduino.h>
#include <Wire.h>

class IR_Seeker {
	public:
		IR_Seeker(int device);
		void readValues();
		int getDirection();
		int seekerValues[5];
	private:
		int _device;
		int readi2c(int address);
}

#endif