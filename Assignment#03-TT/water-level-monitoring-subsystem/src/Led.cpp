#include "Led.h"

Led::Led(int pin) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->state = false;
}

void Led::on() {
  Serial.println("Imposto il led: "+ String(this->pin) + " a HIGH");
  digitalWrite(this->pin, HIGH);
  this->state = true;
}

void Led::off() {
  Serial.println("Imposto il led: "+ String(this->pin) + " a LOW");
  digitalWrite(this->pin, LOW);
  this->state = false;
}

bool Led::isOn() {
  return this->state;
}