void setup(){
  //устанавливаем соединение с bluetooth-модулем на скорости 115200
  Serial2.begin(9600);
  //устанавливаем соединение с персональным компьютером на скорости 9600
  Serial.begin(9600);
  delay(100);
  Serial.println("Start programm");
  delay(100);
}

void loop(){
  //если на модуль пришли данные со стороны мобильного устройства
  if(Serial2.available()){
    //читаем их
    char a = (char)Serial2.read();
    //отправляем на ПК
    Serial.write(a);
    }
  //если пришли данные со стороны ПК
  if(Serial.available()){
    //читаем их
    char a = (char)Serial.read();
    //отправляем на ПК
    Serial2.write(a);
  }
  delay(10);
}

