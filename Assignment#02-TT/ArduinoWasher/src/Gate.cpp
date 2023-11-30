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
  Serial.println("angle: " + String(this->servo.read()));
  delay(101);
}

void Gate::close() {
  this->servo.write(100);
  Serial.println("angle: " + String(this->servo.read()));
  delay(101);
}

void Gate::stop() {
  this->servo.write(90);
}