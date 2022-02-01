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
//устанавливаем различные уровни на пинах порта -
//мотор начинает вращение
for(int i=70; i<255; i=i+2){
  analogWrite (armServoPin, i);
  Serial.println(i);
  //ждём
  delay(500);
  
}

for(int i=255; i>=70; i=i-2){
  analogWrite (armServoPin, i);
  Serial.println(i);
  //ждём
  delay(500);
}

//ждём 2 секунды
delay(2000);

}

