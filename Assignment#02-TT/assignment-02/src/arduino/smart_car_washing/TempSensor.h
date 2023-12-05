#ifndef __TEMPERATURE__
#define __TEMPERATURE__

#include <Arduino.h>

/**
 * Class that handles the temperature sensor
*/
class TempSensor {
  int pin;
public:
  /**
   * Initialize the temperature sensor
   * @param pin The pin to use
  */
  TempSensor(int pin);
  /**
   * Get the temperature
   * @return The temperature
  */
  float getTemperature();
};

#endif