#ifndef __SONAR__
#define __SONAR__

#include <Arduino.h>

class Sonar{
    int trigPin;
    int echoPin;
public:
    Sonar(int trigPin, int echoPin);
    float getDistance();
};

#endif