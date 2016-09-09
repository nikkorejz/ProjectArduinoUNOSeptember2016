#include "Motors.h" //Подсоединяем Motors.h
#include "Sensors.h" //Подсоединяем Sensors.h
#include <LiquidCrystal.h> //Подсоединяем библиотеку управления экраном (80*14)

#define LEFT_SENSOR_PIN  A0 //Думаю понятно (если нет, то мне нечем помочь)
#define RIGHT_SENSOR_PIN A1

#define STATE_STOP 0 //Просто константы
#define STATE_FORWARD 1
#define STATE_LEFT 2
#define STATE_RIGHT 3
#define STATE_BACKWARD 4

Motors motors; //Объявление классов
Sensors sensors;

int DIR_1 = 4; //PIN'Ы
int DIR_2 = 7;
int SPEED_1 = 5;
int SPEED_2 = 6;

int potPin = A4;

LiquidCrystal lcd(2, 3, 10, 11, 12, 13); //Инициализация экрана

String currentStateString = ""; //Опционально. Для удобства.

int state; //Текущее состояние

void setup() {
  
  motors.attach(DIR_1, DIR_2, SPEED_1, SPEED_2); //Подключение моторчиков
  
  state = STATE_STOP; //Изначально машина стоит, значит состояние STATE_STOP
  
  lcd.begin(16, 2); 
  lcd.print("Hello");
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);  
 
}

void loop() {
  
 sensors.attach(LEFT_SENSOR_PIN, RIGHT_SENSOR_PIN); //Подключение сенсоров
 
 int PP = analogRead(potPin); //Считывание показания потенциометра [0..1024]
 PP = PP / 4; //Потому что MAX = 255 ИЛИ (1024/4)
 
// int state = sensors.getAction();
  
 switch(state) {
   case STATE_STOP: //Если стоит, то едем вперед
     if (sensors.getRight() && sensors.getLeft()) {
       state = STATE_FORWARD;
     }
     break;
   case STATE_FORWARD:
      motors.forward(PP);
      printString("OK, LET'S GO!"); 
      if (!sensors.getRight() && sensors.getLeft()) { //Уперлись правым сенсором в трек
        state = STATE_RIGHT;
      } else if (sensors.getRight() && !sensors.getLeft()) { //Уперлись левым сенсором в трек
        state = STATE_LEFT;
      } else if (!sensors.getRight() && !sensors.getLeft()) { //Иначе под нами пустота
        state = STATE_BACKWARD; 
      }
      break;
    case STATE_LEFT: //Аналогичный принцип. Едем налево
      motors.accelerateLeft(PP);
      printString("GO LEFT!");
      break;
    case STATE_RIGHT: //Направо
      motors.accelerateRight(PP);
      printString("GO RIGHT!");
      break;
    case STATE_BACKWARD: //До сих пор непонятно? 
      motors.backward();
      printString("TEAM, FALL BACK!!!");
      if (sensors.getRight() && sensors.getLeft()) {
        state = STATE_FORWARD;
      } 
      break;
  } 
  
  Serial.println(PP); 
}

void printString(String str) { //Функция для вывода строки на экран
  if (str == currentStateString) {
    return;
  } 
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  lcd.print(str);
  currentStateString = str;
  delay(1000);
}

