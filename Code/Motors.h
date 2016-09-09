#include <Arduino.h>

class Motors {
 public:
   void forward(int vel);
   void backward();
   void accelerateRight(int velocity);
   void accelerateLeft(int velocity);
   void left();
   void right();
   void attach(int pin1, int pin2, int pin3, int pin4);
   Motors();
 private:
   void go(int velocity, int right, int left);
   int pin_dir_1, pin_dir_2, pin_speed_1, pin_speed_2, state;
};
