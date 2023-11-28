#include "LcdTask.h"

LcdTask::LcdTask(const char* message) {
  this->lcd = new LcdDisplay();
  this->lcd->init();
  this->message = message;
}

void LcdTask::init(int period) {
  Task::init(period);
}

void LcdTask::tick() {
  if (!this->lcd->getPrintStatus()) {
    this->lcd->print(message);
  }
}