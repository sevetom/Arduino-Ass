#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include <Arduino.h>

#define POT_MIN 20
#define POT_MAX 900

class Potentiometer {
private:
    int pin;
    int min;
    int max;
public:
    Potentiometer(int pin, int min, int max);
    int getValue();
};

#endif