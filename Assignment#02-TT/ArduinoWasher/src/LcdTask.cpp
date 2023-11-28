#include "LcdTask.h"

LcdTask::LcdTask() {
  this->lcd = new LcdDisplay();
  this->lcd->init();
}

void LcdTask::init(int period) {
  Task::init(period);
}

void LcdTask::tick() {
  if (!this->lcd->getPrintStatus()) {
    this->lcd->print("Welcome", 4);
  }
}