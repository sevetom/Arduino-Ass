#include "Pir.h"

Pir::Pir(int pin) {
  this->pin = pin;
  pinMode(this->pin, INPUT);
  Serial.print("Calibrating sensor...");
  //for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
  //  Serial.print(".");
  //  delay(1000);
  //}
  Serial.println("done");
  Serial.println("PIR SENSOR READY.");
}

void Pir::setInterrupt(interruptFun interruptFunction, bool attach) {
  if (attach) {
    attachInterrupt(digitalPinToInterrupt(this->pin), interruptFunction, CHANGE);
  } else {
    detachInterrupt(digitalPinToInterrupt(this->pin));
  }
}