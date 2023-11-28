#include "LedTask.h"

LedTask::LedTask(int pin, ledMode mode) {
  this->led = new Led(pin);
  this->mode = mode;
}

void LedTask::init(int period) {
  Task::init(period);
}

void LedTask::tick() {
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
}