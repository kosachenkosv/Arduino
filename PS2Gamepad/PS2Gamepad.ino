/* основа из проекта https://github.com/murproject/MiddleROV2Surface/blob/master/MiddleROV2Surface/GamepadUtils.cpp 
Для прошивки требуется библиотека PsxNewLib. https://github.com/SukkoPera/PsxNewLib 
Она доступна в менеджере библиотек Arduino IDE: Скетч / Покдлючить библиотеку / Управлять библиотеками, 
далее вводим в поиск PsxNewLib и устанавливаем, соглашаясь и на установку зависимостей. 
PsxNewLib зависит от библиотеки DigitalIO и при необходимости, её можно установить аналогичным способом (через менеджер библиотек).

*/

#define SERIAL_DEBUG Serial

#include "GamepadUtils.h"
//#include "MovingAverage.h"

/*
const byte PIN_PS2_ATT = 9;
const byte PIN_PS2_CMD = 6;
const byte PIN_PS2_DAT = 12;
const byte PIN_PS2_CLK = 10;
*/

constexpr int MAX_POWER = 100;

int treshold(int v, int b) {
    if (abs(v) < b) return 0;
    return v;
}

int filterAxis(byte axis) {
    int an = getStickState(axis);
    an -= 127;
    an = treshold(an, 10) * -1;
    an = constrain(an, -127, 127);
    int val = map(an, -127, 127, -MAX_POWER, MAX_POWER);
    return val;
}

int8_t checkBtn(uint16_t btn1, uint16_t btn2) {
    if (getButtonState(btn1)) {
        return 1;
    }
    if (getButtonState(btn2)) {
        return -1;
    }
    return 0;
}


int8_t getManipulator() {
    int speed = 1;
    return checkBtn(buttonL1, buttonL2) * speed;
}

int8_t getSpeedDivider() {
    int multiplier = checkBtn(buttonSquare, buttonCircle);
    if (multiplier == 0) {
        return 2;
    } else if (multiplier == 1) {
        return 4;
    } else if (multiplier == -1) {
        return 1;
    }
}

void setup() {
  Serial.begin(115200);
  //Serial.begin(230400);
  delay(50);
  Serial.println("Starting prg...");
}

int8_t getMotorButton() {
  int speed = 1;
  return checkBtn(buttonTriangle, buttonCross) * speed;
}

void loop() {
  
    readGamepad();

    int y, x, z = 0, t = 0;
    y = filterAxis(stickLY);
    x = filterAxis(stickLX);
    z = filterAxis(stickRY);
    t = filterAxis(stickRX);

        printButtons();

    SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(getStickState(stickLY)); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(getStickState(stickLX)); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(getStickState(stickRY)); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(getStickState(stickRX)); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.println("");

    SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(y); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(x); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(z); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.print(t); SERIAL_DEBUG.print("\t");
    SERIAL_DEBUG.println("");

  delay(10);
 
}
