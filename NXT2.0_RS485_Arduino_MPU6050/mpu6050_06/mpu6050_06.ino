//Пример получения углов через DPM
// by Kosachenko S.V.
//Ждет через RS485 на SoftwareSerial команду "1" = "передать угол Z c гироскопа MPU6050"
//Pins:
// 10 - RX SoftSerial (RO MAX485)
// 11 - TX SoftSerial (DI MAX485)
// 12 - RE/DE MAX485 (low - recive, high - send)
// A5 - SCL MPU6050 (i2c)
// A4 - SDA MPU6050 (i2c)
//
// LEGO NXT2.0:
// Blue (1 pin) A MAX485
// Yellow (2 pin) B MAX485
// Green (3 pin) Vin Arduino
// Red (4 pin) GND Arduino & GND RS485 & GND MPU6050
// Black - no
// White - no

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;

uint8_t fifoBuffer[45];         // буфер

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
int flag = 0;

void setup() {
  Serial.begin(57600);
  mySerial.begin(57600);
  Wire.begin();
  //Wire.setClock(1000000UL);   // разгоняем шину на максимум

  pinMode(12, OUTPUT); // pin 12 - RE/DE MAX485 режим приема/передачи (low - recive, high - send)
  digitalWrite(12, LOW); // прием для MAX485

  pinMode(13, OUTPUT); // pin 13 LED
  digitalWrite(13, LOW);

  // инициализация DMP
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
}

void loop() {
  static uint32_t tmr;
  if (millis() - tmr >= 11) {  // таймер на 11 мс (на всякий случай)
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      // переменные для расчёта (ypr можно вынести в глобал)
      Quaternion q;
      VectorFloat gravity;
      float ypr[3];

      // расчёты
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

      if (mySerial.available() > 0) {
          int val = mySerial.read();
          if (val == '1') { // пришла команда от LEGO NXT "1" - "отправить угол гироскопа"
            int angle = (int)(180.0*ypr[0]/3.1416);
            digitalWrite(13, HIGH); //включить светодиод на ардуино
            Serial.print(">");
            Serial.println(val);
            Serial.print("<");
            Serial.println((int)(180.0*ypr[0]/3.1416)); // вокруг оси Z
            digitalWrite(12, HIGH); // передача для MAX485
            mySerial.write(angle & 0xFF); // передаем младший байт числа angle
            mySerial.write((angle>>8) & 0xFF); // передаем старший байт числа angle
            digitalWrite(12, LOW); // прием для MAX485
            digitalWrite(13, LOW); //выключить светодиод на ардуино
          }
      }
      
            // выводим результат в радусах (-179, 179) раз в секунду
            if (millis()/500 % 2 && flag) {
              Serial.println((int)(180.0*ypr[0]/3.1416)); // вокруг оси Z
              flag = 0;
            }
            if (millis()/500 % 2 == 0) flag = 1;
            
            // выводим результат в радианах (-3.14, 3.14)
            //Serial.print(',');
            /*
            Serial.print(ypr[0]); // вокруг оси Z
            Serial.print(',');
            Serial.print(ypr[1]); // вокруг оси Y
            Serial.print(',');
            Serial.print(ypr[2]); // вокруг оси X
            Serial.println();
            */
            // для градусов можно использовать degrees()
      //    }
      //}

      tmr = millis();  // сброс таймера
    }
  }
}
