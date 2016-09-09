#include "Sensors.h"

#define STATE_STOP 0
#define STATE_FORWARD 1
#define STATE_LEFT 2
#define STATE_RIGHT 3
#define STATE_BACKWARD 4

Sensors::Sensors() {

}

void Sensors::attach(int pinLeft, int pinRight) {
  this -> leftSensor = !digitalRead(pinLeft);
  this -> rightSensor = !digitalRead(pinRight);
}

int Sensors::getAction() {
  
  if (this -> leftSensor && this -> rightSensor) {
    return STATE_FORWARD;
  } 
  else if (!this -> leftSensor && this -> rightSensor) {
    return STATE_RIGHT; 
  } 
  else if (!this -> leftSensor && !this -> rightSensor) {
    return STATE_BACKWARD;  
  }
  else {
    return STATE_LEFT;
  }
  
}
  
boolean Sensors::getRight() {
  return this -> rightSensor; 
}

boolean Sensors::getLeft() {
  return this -> leftSensor; 
}



