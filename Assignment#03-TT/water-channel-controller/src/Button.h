#ifndef __BUTTON__
#define __BUTTON__

#include <Arduino.h>

#define BOUNCE_TIME 100

/**
 * Class to handle a button
*/
class Button{
  int pin;
  long prevts;
  using InterruptFunction = void (*)(void);
public:
  /**
   * Initialize a button for input
   * @param pin The pin number of the button
  */
  Button(int pin);
  /**
   * Attach ore detach an interrupt to the button
   * @param intFun The function to call when the button is pressed
   * @param attach Whether to attach or detach the interrupt
  */
  void setInterrupt(InterruptFunction intFun, bool attach);

  /**
   * Tries to avoid the button bouncing
   * @return false if the button is bouncing, true otherwise
  */
  bool avoidBouncing();
};

#endif