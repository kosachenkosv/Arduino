//Управляем лодкой с помощью BLUETOOTH.
//В качестве управляющего устройства используем ANDROID устройство с программой Bluetooth RC Controller.
// https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=ru&gl=US
// исходник из https://www.drive2.ru/b/2867939/

#include <Servo.h>
#include <SoftwareSerial.h>

// *********************** Установка выводов моторов ************************
int MotorSpeed = 3; // Левый (А) мотор СКОРОСТЬ — ENA
int MotorIN1 = 4; // Левый (А) мотор ВПЕРЕД — IN1
int MotorIN2 = 5; // Левый (А) мотор ВПЕРЕД — IN2
int pinServo = 6; // Servo для руля

int speed = 250;
int pos = 90;

Servo myservo;

SoftwareSerial mySerial(10, 11); // RX, TX

// ********************** Для управления по блютуз ****************************
char btCommand = 'S';// Задаем переменную BLUETOOTH команда — по умолчанию "S" — СТОП

// ********************************** SETUP ***********************************
void setup ()
{
//Serial.begin (9600); //Включаем серйиный порт — скрость 9600
Serial.begin (9600); //Включаем серйиный порт — для bluetooth модуля
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
mySerial.begin(9600);

//****************** Настраиваем параметры выводов ARDUINO ******************
pinMode (MotorIN1, OUTPUT);
pinMode (MotorIN2, OUTPUT);
pinMode (MotorSpeed, OUTPUT);

myservo.attach(pinServo); //подключаем серво к порту
delay(1000);
myservo.write(pos);
delay(500);

}
// ****************** Задаем основные направления движения ******************
void forward (int a) // ВПЕРЕД
{
digitalWrite (MotorIN1, LOW);
digitalWrite (MotorIN2, HIGH);
analogWrite (MotorSpeed, speed);
delay (50);
}

void stopp (int f) // СТОП
{
digitalWrite (MotorIN1, LOW);
digitalWrite (MotorIN2, LOW);
analogWrite (MotorSpeed, 0);
delay (50);
}
void back (int g) // НАЗАД
{
digitalWrite (MotorIN1, HIGH);
digitalWrite (MotorIN2, LOW);
analogWrite (MotorSpeed, speed);
delay (50);
}

void left (int b) // ПОВОРОТ ВПРАВО (одна сторона)
{
  if (pos <= 160) { 
    pos = pos + 10;
    myservo.write(pos);
    delay(15);
  }
}
void right (int c) // ПОВОРОТ ВЛЕВО (одна сторона)
{
  if (pos >= 20) { 
    pos = pos - 10;
    myservo.write(pos);
    delay(15);
  }
}


// ********************* Управление по БЛЮТУЗ ****************************
void loop()
{
  if (mySerial.available() > 0)// В случае если в "Серийном порту" есть информация
  {
    btCommand = mySerial.read();
    //btCommand = Serial.read(); // Считываем инвормацию с "Серийного порта"
    Serial.write(btCommand); // Печатаем инвормацию с "Серийного порта" — необходио в слуае отладки программы
    switch (btCommand)// Отрабатывем в соотвествии с поступившей командой
    {
    case 'F':
    forward (3); // едем ВПЕРЕД
    break;
    case 'B':
    back (3); // едем НАЗАД
    break;
    case 'R':
    right (3); // поворачиваем ВПРАВО
    break;
    case 'L':
    left (3); // поворачиваем ВЛЕВО
    break;
    case '0':
    speed = 0; // скорость
    break;
    case '1':
    speed = 27; // скорость
    break;
    case '2':
    speed = 54; // скорость
    break;
    case '3':
    speed = 83; // скорость
    break;
    case '4':
    speed = 111; // скорость
    break;
    case '5':
    speed = 139; // скорость
    break;
    case '6':
    speed = 167; // скорость
    break;
    case '7':
    speed = 194; // скорость
    break;
    case '8':
    speed = 222; // скорость
    break;
    case '9':
    speed = 250; // скорость
    break;
    case 'S':
    stopp (3); // СТОП!
    }
  }
}
