#ifndef __PIR__
#define __PIR__

#include <Arduino.h>
#include <EnableInterrupt.h>

#define CALIBRATION_TIME_SEC 3

class Pir{
    bool detectedStatus;
    int pin;
public:
    Pir(int pin);
    void init();
    bool isDetected();
    void setDetected(bool detected);
    void getDetectedStatus();
    void enInterrupt(interruptFunctionType interruptFunction);
    void disInterrupt();
};

#endif