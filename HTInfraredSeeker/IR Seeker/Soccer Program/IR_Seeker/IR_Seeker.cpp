#include "IR_Seeker.h"

IR_Seeker::IR_Seeker(int device) {
	_device = device;
	seekerValues = {0};
}

int IR_Seeker::readi2c(int address) {
  Wire.beginTransmission(_device);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(_device, 1);
  if(1 <= Wire.available())
    return Wire.read();
  return -1;
}

void IR_Seeker::readValues() {
	for(int x = 0; x < 5; x++) {
		seekerValues[x] = readi2c(0x5A + x);
	}
}

int IR_Seeker::getDirection() {
	return readi2c(_device, 0x49);
}