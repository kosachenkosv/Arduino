void setup() {
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
      Serial.print("Joystick1: ");
      Serial.print(valueInt1+10);
      Serial.print(" ");
      Serial.println(valueInt2+10);
      //analogWrite(11, (valueInt+10)*12); //Значения от джойстика -10 до 10 преобразуются в сигнал 0 - 240
    }
    //if (key.equals("red")) analogWrite(10, valueInt); //Слайдер
    //if (key.equals("all")){ analogWrite(9, valueInt); analogWrite(10, valueInt); analogWrite(11, valueInt);} //Слайдер
    if (key.equals("arm_on")) { //Захват сжать Claw +
        Serial.println("Claw +");
        Serial2.println("display Claw +");
      }
    if (key.equals("arm_re")) { //Захват разжать Claw -
        Serial.println("Claw -");
        Serial2.println("display Claw -");
      }
    if (key.equals("arm_up")) { //Arm Up
        Serial.println("Arm UP");
        Serial2.println("display Arm UP");
      }
    if (key.equals("arm_dw")) { //Arm Down
        Serial.println("Arm DOWN");
        Serial2.println("display Arm DOWN");
      }

    if (key.equals("arm_off")){//Arm и Захват OFF
        Serial.println("OFF");
        Serial2.println("display OFF");
      }
    if (key.equals("stop_on")){//Stop ON
        Serial.println("Stop ON");
        Serial2.println("display Stop ON");
      }
    if (key.equals("stop_off")){//Stop OFF
        Serial.println("Stop OFF");
        Serial2.println("display Stop OFF");
      }

  }
}
