#ifndef __BUTTON__
#define __BUTTON__

#include <Arduino.h>

class Button{
    int pin;
    using InterruptFunction = void (*)(void);
public:
    Button(int pin);
    void setInterrupt(InterruptFunction intFun, bool attach);
};

#endif