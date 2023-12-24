#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin, int min, int max) {
    this->pin = pin;
    this->min = min;
    this->max = max;
}

int Potentiometer::getValue() {
    return map(analogRead(this->pin), POT_MIN, POT_MAX, min, max);
}