#include "Pir.h"

Pir::Pir(int pin) {
  this->pin = pin;
}

void Pir::init() {
  pinMode(this->pin, INPUT);
  Serial.print("Calibrating sensor... ");
  for(int i = 0; i < CALIBRATION_TIME_SEC; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("PIR SENSOR READY.");
}

bool Pir::isDetected() {
  return digitalRead(this->pin) == HIGH;
}

void Pir::setDetected(bool detected) {
  this->detectedStatus = detected;
}

void Pir::getDetectedStatus() {
  Serial.print("Detected status: ");
  Serial.println(this->detectedStatus);
}

void Pir::setInterrupt(interruptFun interruptFunction, bool attach) {
  if (attach) {
    attachInterrupt(digitalPinToInterrupt(this->pin), interruptFunction, CHANGE);
  } else {
    detachInterrupt(digitalPinToInterrupt(this->pin));
  }
}