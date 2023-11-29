#ifndef __GATE__
#define __GATE__

#include <Arduino.h>
#include <Servo.h>

class Gate{
  int pin;
  Servo servo;
public:
  Gate(int pin);
  void on();
  void off();
  void open();
  void close();
  void stop();
};

#endif