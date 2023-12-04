#ifndef __SONAR__
#define __SONAR__

#include <Arduino.h>

/**
 * Class to handle the sonar sensor
*/
class Sonar{
  int trigPin;
  int echoPin;
public:
  /**
   * Initialize the sonar sensor
   * @param trigPin The pin to use for the trigger
   * @param echoPin The pin to use for the echo
  */
  Sonar(int trigPin, int echoPin);
  /**
   * Get the distance from the sonar sensor
   * @return The distance from the sonar sensor
  */
  float getDistance();
};

#endif