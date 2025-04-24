//Пример получения углов через DPM
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;

uint8_t fifoBuffer[45];         // буфер

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //Wire.setClock(1000000UL);   // разгоняем шину на максимум

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

      //if (Serial.available() > 0) {
      //    int val = Serial.read();
      //    if (val == 's') { // if incoming serial is "s"
            // выводим результат в радианах (-3.14, 3.14)
            Serial.print(ypr[0]); // вокруг оси Z
            Serial.print(',');
            Serial.print(ypr[1]); // вокруг оси Y
            Serial.print(',');
            Serial.print(ypr[2]); // вокруг оси X
            Serial.println();
            // для градусов можно использовать degrees()
      //    }
      //}

      tmr = millis();  // сброс таймера
    }
  }
}
