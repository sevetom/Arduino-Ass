#ifndef __TEMPERATURE__
#define __TEMPERATURE__

#include <Arduino.h>

class TempSensor {
    int pin;
public:
    TempSensor(int pin);
    float getTemperature();
};

#endif