//указываем пины, отвечающие за управление портом M2
const int motorPinOne = 6;
const int motorPinTwo = 7;
void setup() {
//конфигурируем пины порта М1 на вывод сигнала
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
}
void loop() {
//устанавливаем различные уровни на пинах порта -
//мотор начинает вращение
analogWrite (motorPinOne, 230);
digitalWrite (motorPinTwo, LOW);
//ждём 2 секунды
delay(2000);

//устанавливаем одинаковые уровни на пинах порта -
//мотор останавливается
digitalWrite (motorPinOne, LOW);
digitalWrite (motorPinTwo, LOW);
//ждём 2 секунды
delay(2000);

digitalWrite (motorPinOne, LOW);
analogWrite (motorPinTwo, 230);
//ждём 2 секунды
delay(2000);

//устанавливаем одинаковые уровни на пинах порта -
//мотор останавливается
digitalWrite (motorPinOne, LOW);
digitalWrite (motorPinTwo, LOW);
//ждём 2 секунды
delay(2000);

}

