#include "Gate.h"

Gate::Gate(int pin) {
  this->pin = pin;
  this->myservo.attach(this->pin);
}

void Gate::open90() {
  this->myservo.write(80);
  delay(500);
  this->myservo.write(90);
}

void Gate::close90() {
  this->myservo.write(100);
  delay(550);
  this->myservo.write(90);
}