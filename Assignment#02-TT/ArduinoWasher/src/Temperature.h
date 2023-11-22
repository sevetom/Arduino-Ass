#ifndef __TEMPERATURE__
#define __TEMPERATURE__

#include <Arduino.h>

class Temperature{
    int pin;
public:
    Temperature(int pin);
    float getTemperature();
};

#endif