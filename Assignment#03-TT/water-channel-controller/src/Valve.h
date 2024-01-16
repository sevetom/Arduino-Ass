#ifndef __VALVE_H__
#define __VALVE_H__

#include <Servo.h>

#define MIN_ANGLE 0
#define MAX_ANGLE 180

class Valve {

public:
  Valve(int pin);

  void on();
  void setPosition(int angle);
  void off();
  int getMinAngle();
  int getMaxAngle();
    
private:
  int pin; 
  Servo motor; 
};

#endif
