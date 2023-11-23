#include "LedTask.h"

LedTask::LedTask(int pin) {
  this->led = new Led(pin);
}

void LedTask::init(int period) {
  Task::init(period);
}

void LedTask::tick() {
  if (!this->led->isOn()) {
    this->led->on();
  }
}