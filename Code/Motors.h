#include <Arduino.h> 

class Motors {
 public:
   void forward(int vel); //Вперед
   void backward(); //Назад
   void accelerateRight(int velocity); //Плавно направо
   void accelerateLeft(int velocity); //Плавно налево
   void left(); //Резко налево
   void right(); //Резко направо
   void attach(int pin1, int pin2, int pin3, int pin4); //Подключение
   Motors();
 private:
   void go(int velocity, int right, int left);
   int pin_dir_1, pin_dir_2, pin_speed_1, pin_speed_2, state;
};
