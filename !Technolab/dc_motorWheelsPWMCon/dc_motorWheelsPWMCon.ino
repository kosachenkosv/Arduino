/*
Мотор 393 подключен через M1
вместо библиотеки Servo, которая блокирует порт M1(46,45)
мы управляем вращением двигателея через ШИМ (PWM)
командой
analogWrite (Pin, valueInt);

,где: 
Pin - порт управления Motor

valueInt задает вращение:
-254..+254
*/
//порт, к которому подключён мотор Arm через Motor Controller 29
const int armServoPin = 5;
//порт, к которому подключён мотор Claw через Motor Controller 29
const int clawServoPin = 2;

//порты, к которым подключены Моторы колес
// motor1 M1 (Left)
const int motorM1PinOne = 46;
const int motorM1PinTwo = 45;
// motor1 M2 (Right)
const int motorM2PinOne = 6;
const int motorM2PinTwo = 7;

//скорость моторов на колесах
int speedMotor = 150;

//задаем направление моторов вращения в роботе
// motor1(левый) развернут и при движении робота вперед
//вращается назад, т.е. против часовой
int motor1SetReversed= true;
int motor2SetReversed= false;

void setup() {

  //инициализируем соединение с ПК по последовательному порту
  //со скоростью 9600 бод
  Serial.begin(9600); 

  //конфигурируем пины порта М1 на вывод сигнала
  pinMode(armServoPin, OUTPUT);
  pinMode(clawServoPin, OUTPUT);
}
void loop() {

    String s = "";

  while (Serial.available() > 0){ //Если пришли данные, то записать в переменную s
    char c = Serial.read();   
    s += c;   
    delay(2);  //ОБЯЗАТЕЛЬНАЯ ПАУЗА для разделения сообщений                
  } 
  if (s!=""){
    int valueInt = s.toInt(); //Переводим значение в int
    Serial.println(valueInt);
    powerMotor1(valueInt); //M1 мотор
    delay(500);
  }
}

//управление мотором1
void powerMotor1(int speedValue){
  int direction = motor1SetReversed ? -1 : 1;
  if (speedValue == 0)  {
    digitalWrite(motorM1PinOne, LOW);
    digitalWrite(motorM1PinTwo, LOW);
   }
  if (direction*speedValue > 0)  {
    digitalWrite(motorM1PinOne, LOW);
    analogWrite(motorM1PinTwo, abs(speedValue));
   }
  if (direction*speedValue < 0)  {
    analogWrite(motorM1PinOne, abs(speedValue));
    digitalWrite(motorM1PinTwo, LOW);
   }
  Serial.print("motor1:");
  Serial.println(speedValue);
}

//управление мотором2
void powerMotor2(int speedValue){
  int direction = motor2SetReversed ? -1 : 1;
  if (speedValue == 0)  {
    digitalWrite(motorM2PinOne, LOW);
    digitalWrite(motorM2PinTwo, LOW);
   }
  if (direction*speedValue > 0)  {
    digitalWrite(motorM2PinOne, LOW);
    analogWrite(motorM2PinTwo, abs(speedValue));
   }
  if (direction*speedValue < 0)  {
    analogWrite(motorM2PinOne, abs(speedValue));
    digitalWrite(motorM2PinTwo, LOW);
   }
  Serial.print("motor2:");
  Serial.println(speedValue);
}

