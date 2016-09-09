#include <Arduino.h>

class Sensors {
  public:
    Sensors();
    int getAction();
    boolean getRight();
    boolean getLeft();
    void attach(int pinLeft, int pinRight);
  private:
    boolean leftSensor, rightSensor;
};

