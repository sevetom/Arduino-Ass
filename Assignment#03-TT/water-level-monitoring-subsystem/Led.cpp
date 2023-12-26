#include "Led.h"

Led::Led(int pin) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->state = false;
}

void Led::on() {
  digitalWrite(this->pin, HIGH);
  this->state = true;
}

void Led::off() {
  digitalWrite(this->pin, LOW);
  this->state = false;
}

bool Led::isOn() {
  return this->state;
}