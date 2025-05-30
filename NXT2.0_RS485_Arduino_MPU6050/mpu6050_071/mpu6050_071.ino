//Пример получения углов через DPM
// by Kosachenko S.V.
//Ждет через RS485 на SoftwareSerial команду "1" = "передать угол Z c гироскопа MPU6050"
//Pins:
// 7(10) - RX SoftSerial (RO MAX485)
// 8(11) - TX SoftSerial (DI MAX485)
// 9(12) - RE/DE MAX485 (low - recive, high - send)
// (13) - SCK LED освободить
// A5 - SCL MPU6050 (i2c)
// A4 - SDA MPU6050 (i2c)
// Pixy2 - ICSP: MOSI(11) MISO(12) SCK(13) 
//
// LEGO NXT2.0:
// Blue (1 pin) A MAX485
// Yellow (2 pin) B MAX485
// Green (3 pin) Vin Arduino
// Red (4 pin) GND Arduino & GND RS485 & GND MPU6050
// Black - no
// White - no

#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;

uint8_t fifoBuffer[45];         // буфер

#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX
int flag = 0;

int16_t v_x = 0, angle = 0; 
int v_x1, v_x2, v_width, v_width1, v_width2;

void setup() {
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(57600);
  Wire.begin();
  //Wire.setClock(1000000UL);   // разгоняем шину на максимум

  pinMode(9, OUTPUT); // pin 12 - RE/DE MAX485 режим приема/передачи (low - recive, high - send)
  digitalWrite(9, LOW); // прием для MAX485

  //pinMode(13, OUTPUT); // pin 13 LED
  //digitalWrite(13, LOW);
  
  pixy.init();

  // инициализация DMP
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
}

void loop() {
  uint8_t val = 0;
  int val_signature=0;  
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
      angle = (int)(180.0*ypr[0]/3.1416);

      if (mySerial.available() > 0) {
        val = mySerial.read(); 
		    if (val == '1') val_signature = 1;
		    if (val == '2') val_signature = 2;
        
        if (val == '1' || val == '2' ){ // пришла команда от LEGO NXT "1" /"2" - "отправить CamX1 / CamX2"
    			  v_x =0;
    			  //v_y =0;
    			  v_width =0;
    
            // grab blocks!
            pixy.ccc.getBlocks();
    
      			if (pixy.ccc.numBlocks) 
      			{
      				for (int i=0; i<pixy.ccc.numBlocks; i++)
      				{
      					if(pixy.ccc.blocks[i].m_signature == val_signature)
      					{
      						if (pixy.ccc.blocks[i].m_width > v_width)
      						{
      							v_x = pixy.ccc.blocks[i].m_x;
      							//v_y = pixy.ccc.blocks[i].m_y;
      							v_width = pixy.ccc.blocks[i].m_width;
      						}
      					}
      				}
      			}

            //digitalWrite(13, HIGH); //включить светодиод на ардуино
            Serial.print(">");
            Serial.println(val);
            Serial.print("<");
            Serial.println(v_x); // CamX
            digitalWrite(9, HIGH); // передача для MAX485
            mySerial.write(v_x & 0xFF); // передаем младший байт числа angle
            mySerial.write((v_x>>8) & 0xFF); // передаем старший байт числа angle
            delay(1);
            digitalWrite(9, LOW); // прием для MAX485
            //digitalWrite(13, LOW); //выключить светодиод на ардуино
          }

          if (val == '3') { // пришла команда от LEGO NXT "3" - "отправить угол гироскопа"
            angle = (int)(180.0*ypr[0]/3.1416);
            //digitalWrite(13, HIGH); //включить светодиод на ардуино
            Serial.print(">");
            Serial.println(val);
            Serial.print("<");
            Serial.println(angle); // вокруг оси Z
            digitalWrite(9, HIGH); // передача для MAX485
            mySerial.write(angle & 0xFF); // передаем младший байт числа angle
            mySerial.write((angle>>8) & 0xFF); // передаем старший байт числа angle
            //delay(1);
            digitalWrite(9, LOW); // прием для MAX485
            //digitalWrite(13, LOW); //выключить светодиод на ардуино
          }
          
          
          
      }
            
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

      tmr = millis();  // сброс таймера
    }
  }
	// выводим результат в радусах (-179, 179) раз в секунду
	if (millis()/1000 % 2 && flag) {
      v_x1=0;
      v_x2=0;
      v_width1 = 0;
      v_width2 = 0;

      // grab blocks!
      pixy.ccc.getBlocks();
      
      if (pixy.ccc.numBlocks) 
      {
        for (int i=0; i<pixy.ccc.numBlocks; i++)
        {
          if(pixy.ccc.blocks[i].m_signature == 1)
          {
            if (pixy.ccc.blocks[i].m_width > v_width1)
            {
              v_x1 = pixy.ccc.blocks[i].m_x;
              v_width1 = pixy.ccc.blocks[i].m_width;
            }
          }
          if(pixy.ccc.blocks[i].m_signature == 2)
          {
            if (pixy.ccc.blocks[i].m_width > v_width2)
            {
              v_x2 = pixy.ccc.blocks[i].m_x;
              v_width2 = pixy.ccc.blocks[i].m_width;
            }
          }          
        }
      }
  
    Serial.print(pixy.ccc.numBlocks);
    Serial.print(" x1:");
	  Serial.print(v_x1); // CamX1
    Serial.print(" x2:");
    Serial.print(v_x2); // CamX2
	  Serial.print(" a:");
	  Serial.println(angle); // mpu6050
	  flag = 0;
	}
	if (millis()/1000 % 2 == 0) flag = 1;
}
