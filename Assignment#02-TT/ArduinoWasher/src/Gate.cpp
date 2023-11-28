#include "Gate.h"

Gate::Gate(int pin) {
  this->pin = pin;
  this->myservo.attach(this->pin);
}

void Gate::open() {
  this->myservo.write(80);
  Serial.println("DAJEDAJEDAJEDAJEDAJEDAJEDAJEDAJEDAJEDAJEDAJEADAJEDAJEDAJE");
}

void Gate::close() {
  this->myservo.write(100);
}

void Gate::stop() {
  this->myservo.write(90);
}