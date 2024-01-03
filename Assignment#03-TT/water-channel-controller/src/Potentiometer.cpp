#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin, int min, int max) {
    this->pin = pin;
    this->min = min;
    this->max = max;
}

int Potentiometer::getValue() {
    return map(analogRead(this->pin), POT_MIN, POT_MAX, min, max);
}

bool Potentiometer::detectChange() {
    int value = this->getValue();
    if (value != this->currentValue) {
        this->currentValue = value;
        return true;
    }
    return false;
}