#include "Sensors.h" 

#define STATE_STOP 0
#define STATE_FORWARD 1
#define STATE_LEFT 2
#define STATE_RIGHT 3
#define STATE_BACKWARD 4

Sensors::Sensors() {

}

void Sensors::attach(int pinLeft, int pinRight) {
  this -> leftSensor = !digitalRead(pinLeft); //THIS -> НЕ обязателен, если имя переменной и параметра метода НЕ совпадают
  this -> rightSensor = !digitalRead(pinRight); //Это тип BOOLEAN потому что датчик нам дает всего 2 значения, если хотите - используйте INTEGER, никто не запрещает
}

int Sensors::getAction() {
  
  if (this -> leftSensor && this -> rightSensor) { //Если значения одинаковы, то вернём единицу
    return STATE_FORWARD;
  } 
  else if (!this -> leftSensor && this -> rightSensor) { //Если левый врёт, то возвращаем тройку
    return STATE_RIGHT; 
  } 
  else if (!this -> leftSensor && !this -> rightSensor) { //Если оба врут, то возвращаем четверку
    return STATE_BACKWARD;  
  }
  else { //Иначе двойку
    return STATE_LEFT;
  }
  
}
  
boolean Sensors::getRight() { //Вернем PRIVATE переменные
  return this -> rightSensor; 
}

boolean Sensors::getLeft() {
  return this -> leftSensor; 
}



