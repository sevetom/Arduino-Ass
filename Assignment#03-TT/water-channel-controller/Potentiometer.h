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
    int currentValue;
public:
    /**
     * Initialize the potentiometer
     * @param pin The pin number of the potentiometer
     * @param min The minimum value of the potentiometer
     * @param max The maximum value of the potentiometer
    */
    Potentiometer(int pin, int min, int max);
    /**
     * Get the value of the potentiometer
     * @return The value of the potentiometer
    */
    int getValue();
    /**
     * Detect a change in the value of the potentiometer
     * @return true if the value has changed, false otherwise
    */
    bool detectChange();
};

#endif