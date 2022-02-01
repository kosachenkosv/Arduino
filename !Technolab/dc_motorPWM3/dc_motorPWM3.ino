/*
Мотор 393 подключен через Motor Controller 29
вместо библиотеки Servo, которая блокирует порт M1(46,45)
мы управляем вращением двигателея через ШИМ (PWM)
командой
analogWrite (armServoPin, valueInt);

,где: 
armServoPin - порт управления Motor Controller 29

valueInt задает вращение:
122-184 по часовой
188 - стоп
192-254 против часовой
*/


//порт, к которому подключён мотор Arm через Motor Controller 29
const int armServoPin = 5;
//порт, к которому подключён мотор Claw через Motor Controller 29
const int clawServoPin = 2;

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
    analogWrite (armServoPin, valueInt);
    delay(500);
  }
}

