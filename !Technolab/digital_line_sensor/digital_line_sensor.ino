//указываем порт, к которому подключён детектор - 0(48)
const int lineTrackerPort = 48;
//объявляем переменную для работы с детектором
int lineTrackerState = 0;
void setup(){
//конфигурируем выбранный порт на чтение
pinMode(lineTrackerPort, INPUT);
//инициализируем соединение с ПК по последовательному порту
//со скоростью 9600 бод
Serial.begin(9600);
}
void loop(){
//читаем уровень сигнала на выбранном цифровом порту
lineTrackerState=digitalRead(lineTrackerPort);
//выводим в последовательный порт сообщение в зависимости от состояния детектора
//если попал на чёрную линию, уровень становится высоким
if (lineTrackerState == HIGH)
Serial.println("White backgrownd");
else
//если попал на белый фон, на выходе держится низкий уровень
Serial.println("Black line");
//задаем паузу между опросами порта в 50 мс
delay(50);
}

