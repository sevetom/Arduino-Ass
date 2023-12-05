#ifndef __PIR__
#define __PIR__

#include <Arduino.h>

#define CALIBRATION_TIME_SEC 5

/**
 * Class that handles a PIR sensor
*/
class Pir {
  using interruptFun = void (*)(void);
  bool detectedStatus;
  int pin;
public:
  /**
   * Initialize the PIR sensor
   * @param pin The pin to use
  */
  Pir(int pin);
  void setInterrupt(interruptFun interruptFunction, bool attach);
};

#endif