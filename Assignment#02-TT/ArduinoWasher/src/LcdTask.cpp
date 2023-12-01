#include "LcdTask.h"

LcdTask::LcdTask(LcdDisplay* lcd, const char* message) {
  this->lcd = lcd;
  this->message = message;
  this->mode = PRINT;
  this->printStatus = false;
  this->percentage = 0;
}

LcdTask::LcdTask(LcdDisplay* lcd, const char* message, CountDown* timer) {
  this->lcd = lcd;
  this->message = message;
  this->timer = timer;
  this->percentage = 0;
  this->mode = LOADING_BAR;
  this->printStatus = false;
}

void LcdTask::init(int period) {
  Task::init(period);
}

void LcdTask::tick() {
  if (!this->printStatus) {
    this->lcd->clear();
    this->lcd->printLong(this->message);
    this->printStatus = true;
  }
  if (this->mode == LOADING_BAR && this->timer->getTime() >= this->percentage*1000) {
    this->lcd->printText("#", this->percentage, 1);
    this->percentage++;
  }
}

void LcdTask::restart() {
  this->timeElapsed = 0;
  this->percentage = 0;
  this->printStatus = false;
  if (this->mode == LOADING_BAR) {
    this->timer->reset();
  }
}