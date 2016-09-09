#include <Arduino.h> //Просто так надо

class Sensors {
  public:
    Sensors(); //Пустой конструктор
    int getAction(); //Функция для возвращения числа, по которому определяется дальнейшее движение (Использовалось в старой версии, сейчас не нужно)
    boolean getRight(); //Значения правого датчика
    boolean getLeft(); //Левого
    void attach(int pinLeft, int pinRight); //Подключение сенсоров
  private:
    boolean leftSensor, rightSensor; 
};

