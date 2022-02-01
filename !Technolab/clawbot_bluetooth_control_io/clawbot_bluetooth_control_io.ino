/*
ClawBot, управляемый по Bluetooth
Левый мотор M13(5) (через драйвер ШИМ)
Правый мотор M12(2) (через драйвер ШИМ)
Arm(рука) M1 - 6,7 pins
Claw(клешня) M2 - 46, 45 pins

*/

//подключаем библиотеку для работы с моторами по PWM шине
#include <Servo.h>
//инициализируем наши моторы присвоением им имен
Servo leftServo, rightServo;

// motor1 M1 (Arm)
const int motorM1PinOne = 46;
const int motorM1PinTwo = 45;
// motor1 M2 (Claw)
const int motorM2PinOne = 6;
const int motorM2PinTwo = 7;


void setup() {
  //порты M1
  pinMode(motorM1PinOne, OUTPUT);
  pinMode(motorM1PinTwo, OUTPUT);

  //порты M2
  pinMode(motorM2PinOne, OUTPUT);
  pinMode(motorM2PinTwo, OUTPUT);
  
  //указываем порт, к которому подключён мотор M13(5)
  leftServo.attach(5);
  //указываем порт, к которому подключён мотор M10(6)
  rightServo.attach(2);

  Serial2.begin(9600); // инициализация порта BT
  Serial.begin(9600); // инициализация порта
  delay(100);
  Serial.println("Start programm");
  delay(100);
}

void loop() {

  String s = "";

  while (Serial2.available() > 0){ //Если пришли данные, то записать в переменную s
    char c = Serial2.read();   
    s += c;   
    delay(2);  //ОБЯЗАТЕЛЬНАЯ ПАУЗА для разделения сообщений                
  } 
  if (s!=""){
    
    String key = "", value1 = "", value2 = ""; //ключ, значение
   
    int i = 0;
    
    while (i<s.length()){ //Считываем ключ
      if (s[i]==' ') break;
      key += s[i];
      i++;
    }

    if (s[i]==' ') i++;
    
    while (i<s.length()){ //Считываем значение 1
      if (s[i]==' ') break;
      value1 += s[i];
      i++;
    }

    if (s[i]==' ') i++;

    while (i<s.length()){ //Считываем значение 2
      if (s[i]==' ') break;
      value2 += s[i];
      i++;
    }

    int valueInt1 = value1.toInt(); //Переводим значение в int
    int valueInt2 = value2.toInt(); //Переводим значение в int

    if (key.equals("joystick1")){

      leftServo.writeMicroseconds(min(2000, max(1000, 1500 + 50*(-valueInt1 - valueInt2))));
      rightServo.writeMicroseconds(min(2000, max(1000, 1500 + 50*(-valueInt1 + valueInt2))));

      Serial.print("LeftMotor: ");
      Serial.print(  min(2000, max(1000, 1500 + 50*(-valueInt1 - valueInt2))));
      Serial.print(" RightMotor: ");
      Serial.println(min(2000, max(1000, 1500 + 50*(-valueInt1 + valueInt2))));
      //analogWrite(11, (valueInt+10)*12); //Значения от джойстика -10 до 10 преобразуются в сигнал 0 - 240
    }
    //if (key.equals("red")) analogWrite(10, valueInt); //Слайдер
    //if (key.equals("all")){ analogWrite(9, valueInt); analogWrite(10, valueInt); analogWrite(11, valueInt);} //Слайдер
    if (key.equals("arm_on")) { //Захват сжать Claw +

        //Claw +
        digitalWrite(motorM2PinOne, HIGH);
        digitalWrite(motorM2PinTwo, LOW);
      
        Serial.println("Claw +");
        Serial2.println("display Claw +");
      }
    if (key.equals("arm_re")) { //Захват разжать Claw -

        //Claw -
        digitalWrite(motorM2PinOne, LOW);
        digitalWrite(motorM2PinTwo, HIGH);
      
        Serial.println("Claw -");
        Serial2.println("display Claw -");
      }
    if (key.equals("arm_up")) { //Arm Up

        //Arm +
        digitalWrite(motorM1PinOne, HIGH);
        digitalWrite(motorM1PinTwo, LOW);

        Serial.println("Arm UP");
        Serial2.println("display Arm UP");
      }
    if (key.equals("arm_dw")) { //Arm Down

        //Arm -
        digitalWrite(motorM1PinOne, LOW);
        digitalWrite(motorM1PinTwo, HIGH);

        Serial.println("Arm DOWN");
        Serial2.println("display Arm DOWN");
      }

    if (key.equals("arm_off")){//Arm и Захват OFF
        stopAll();
        Serial.println("OFF");
        Serial2.println("display OFF");
      }
    if (key.equals("stop_on")){//Stop ON
        stopAll();
        Serial.println("Stop ON");
        Serial2.println("display Stop ON");
      }
    if (key.equals("stop_off")){//Stop OFF
        stopAll();
        Serial.println("Stop OFF");
        Serial2.println("display Stop OFF");
      }

  }
}

void stopAll(){
  //останавливаем моторы
  leftServo.writeMicroseconds(1500);
  rightServo.writeMicroseconds(1500);

  //Arm
  digitalWrite(motorM1PinOne, LOW);
  digitalWrite(motorM1PinTwo, LOW);
  
  //Claw
  digitalWrite(motorM2PinOne, LOW);
  digitalWrite(motorM2PinTwo, LOW);

  
  //задаем паузу в 2 секунды
  delay (2000);

}

