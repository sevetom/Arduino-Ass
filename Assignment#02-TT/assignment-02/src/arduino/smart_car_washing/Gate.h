#ifndef __GATE__
#define __GATE__

#include <Arduino.h>
#include <Servo.h>

/**
 * Class that uses a servo as a gate
*/
class Gate{
  int pin;
  Servo servo;
public:
  /**
   * Initialize the gate
   * @param pin The pin number of the servo
  */
  Gate(int pin);
  /**
   * Attaches the servo to the pin
  */
  void on();
  /**
   * Detaches the servo from the pin
  */
  void off();
  /**
   * Starts opening the gate
  */
  void open();
  /**
   * Starts closing the gate
  */
  void close();
  /**
   * Stops the gate
  */
  void stop();
};

#endif