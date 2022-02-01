//указываем порт, к которому подключён детектор - A0
const int lineTrackerPort = A0;
//объявляем переменную для работы с детектором
int lineTrackerValue = 0;
void setup(){
//конфигурируем выбранный порт на чтение
pinMode(lineTrackerPort, INPUT);
//инициализируем соединение с ПК по последовательному порту
//со скоростью 9600 бод
Serial.begin(9600);
}
void loop(){
//читаем уровень сигнала на выбранном цифровом порту
lineTrackerValue=analogRead(lineTrackerPort);
//выводим в последовательный порт сообщение в зависимости от состояния детектора
Serial.println(lineTrackerValue);
//задаем паузу между опросами порта в 50 мс
delay(50);
}

