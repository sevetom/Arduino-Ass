#ifndef __GATE__
#define __GATE__

#include <Arduino.h>
#include <Servo.h>

#define MIN_ANGLE 0
#define MAX_ANGLE 180

/**
 * Class that uses a servo as a gate
*/
class Gate{
  int pin;
  Servo servo;
  int currentAngle;
public:
  /**
   * Initialize the gate
   * @param pin The pin number of the servo
  */
  Gate(int pin);
  /**
   * Sets the gate to a certain angle if possible
  */
  void setAngle(int angle);
};

#endif