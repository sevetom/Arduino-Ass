#include "LedTask.h"

LedTask::LedTask(Led* led, ledMode mode) {
  this->led = led;
  this->mode = mode;
}

void LedTask::init(int period) {
  Task::init(period);
}

void LedTask::tick() {
  Serial.println("LedTask " + String(this->led->isOn()));
  switch (this->mode) {
    case ON:
      if (!this->led->isOn()) {
        this->led->on();
      }
      break;
    case OFF:
      if (this->led->isOn()) {
        this->led->off();
      }
      break;
    case BLINK:
      if (this->led->isOn()) {
        this->led->off();
      } else {
        this->led->on();
      }
      break;
  }
  Serial.println("LedTask end");
}