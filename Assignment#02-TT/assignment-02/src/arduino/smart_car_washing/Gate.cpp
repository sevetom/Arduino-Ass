#include "Gate.h"

Gate::Gate(int pin) {
  this->pin = pin;
}

void Gate::on() {
  this->servo.attach(this->pin);
}

void Gate::off() {
  this->servo.detach();
}

void Gate::open() {
  this->servo.write(80);
  delay(101);
}

void Gate::close() {
  this->servo.write(100);
  delay(105);
}

void Gate::stop() {
  this->servo.write(90);
}