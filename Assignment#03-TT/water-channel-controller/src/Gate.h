#ifndef __GATE__
#define __GATE__

#include <Arduino.h>
#include <Servo.h>

#define GATE_MIN_ANGLE 0
#define GATE_MAX_ANGLE 180

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
   * @param angle The angle to set the gate to
  */
  void setAngle(int angle);
  /**
   * Gets the min angle of the gate
  */
  int getMinAngle();
  /**
   * Gets the max angle of the gate
  */
  int getMaxAngle();
};

#endif