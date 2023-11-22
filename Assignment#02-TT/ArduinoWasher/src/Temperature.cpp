#include "Temperature.h"

Temperature::Temperature(int pin){
    this->pin = pin;
}

float Temperature::getTemperature(){
    int reading = analogRead(pin);
    int value_in_mV = 4.8876 * reading;
    double value_in_C = value_in_mV * 0.1;
    return value_in_C;
}