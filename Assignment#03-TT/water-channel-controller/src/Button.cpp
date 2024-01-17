#include "Button.h"

Button::Button(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
    this->prevts = 0;
}

void Button::setInterrupt(InterruptFunction intFun, bool attach){
    if(attach){
        attachInterrupt(digitalPinToInterrupt(pin), intFun, RISING);
    }else{
        detachInterrupt(digitalPinToInterrupt(pin));
    }
}

bool Button::avoidBouncing(){
    long ts = millis();
    if (ts - prevts > BOUNCE_TIME) {
        prevts = ts;
        return true;
    }
    return false;
}