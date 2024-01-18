#ifndef __SONAR__
#define __SONAR__

#define PING_TIME 200

#include <NewPing.h>

/**
 * Class to handle the sonar sensor
*/
class Sonar {
    NewPing* sonar;
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
     * Get the distance from the sonar sensor in cm
     * @return The distance from the sonar sensor in cm
    */
    float getDistance();
};

#endif