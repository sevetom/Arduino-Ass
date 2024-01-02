#ifndef __LED__
#define __LED__

#include <Arduino.h>

/**
 * Class that handles a LED
*/
class Led {
  int pin;
  bool state;
public:
  /**
   * Initialize the LED
   * @param pin The pin to use
  */
  Led(int pin);
  /**
   * Turn the LED on
  */
  void on();
  /**
   * Turn the LED off
  */
  void off();
  /**
   * Checks if the LED is on
   * @return True if the LED is on, false otherwise
  */
  bool isOn();
};

#endif