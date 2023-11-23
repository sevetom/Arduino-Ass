#include "LcdTask.h"

LcdTask::LcdTask() {
  this->lcd = new LcdDisplay();
}

void LcdTask::init(int period) {
  Task::init(period);
}

void LcdTask::tick() {
  this->lcd->print("Welcome");
}