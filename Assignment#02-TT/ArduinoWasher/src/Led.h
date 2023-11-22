#ifndef __LED__
#define __LED__

#include <Arduino.h>

class Led {
  int pin;
  bool state;
public:
  Led(int pin);
  void on();
  void off();
  bool isOn();
};

#endif