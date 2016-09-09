#include "Motors.h"
#include "Sensors.h"
#include <LiquidCrystal.h>

#define LEFT_SENSOR_PIN  A0
#define RIGHT_SENSOR_PIN A1

#define STATE_STOP 0
#define STATE_FORWARD 1
#define STATE_LEFT 2
#define STATE_RIGHT 3
#define STATE_BACKWARD 4

Motors motors;
Sensors sensors;

int DIR_1 = 4;
int DIR_2 = 7;
int SPEED_1 = 5;
int SPEED_2 = 6;

int ledPin = 9;
int potPin = A4;

LiquidCrystal lcd(2, 3, 10, 11, 12, 13);

String currentStateString = "";

int state;

void setup() {
  
  motors.attach(DIR_1, DIR_2, SPEED_1, SPEED_2);
  
  state = STATE_STOP;
  
  lcd.begin(16, 2);
  lcd.print("Hello");
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);  
 
}

void loop() {
  
 sensors.attach(LEFT_SENSOR_PIN, RIGHT_SENSOR_PIN);
 
 int PP = analogRead(potPin);
 PP = PP / 4;
 
// int state = sensors.getAction();
  
 switch(state) {
   case STATE_STOP:
     if (sensors.getRight() && sensors.getLeft()) {
       state = STATE_FORWARD;
     }
     break;
   case STATE_FORWARD:
      motors.forward(PP);
      printString("OK, LET'S GO!"); 
      if (!sensors.getRight() && sensors.getLeft()) {
        state = STATE_RIGHT;
      } else if (sensors.getRight() && !sensors.getLeft()) {
        state = STATE_LEFT;
      } else {
        state = STATE_BACKWARD; 
      }
      break;
    case STATE_LEFT:
      motors.accelerateLeft(PP);
      printString("GO LEFT!");
      break;
    case STATE_RIGHT:
      motors.accelerateRight(PP);
      printString("GO RIGHT!");
      break;
    case STATE_BACKWARD:
      motors.backward();
      printString("TEAM, FALL BACK!!!");
      if (sensors.getRight() && sensors.getLeft()) {
        state = STATE_FORWARD;
      } 
      break;
  } 
  
  Serial.println(PP);
  analogWrite(ledPin, PP);
}

void printString(String str) {
  if (str == currentStateString) {
    return;
  } 
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  lcd.print(str);
  currentStateString = str;
  delay(1000);
}

