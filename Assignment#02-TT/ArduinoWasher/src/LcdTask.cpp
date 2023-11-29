#include "LcdTask.h"

LcdTask::LcdTask(LcdDisplay* lcd, const char* message) {
  this->lcd = lcd;
  this->message = message;
  this->mode = PRINT;
}

LcdTask::LcdTask(LcdDisplay* lcd, const char* message, CountDown* timer) {
  this->lcd = lcd;
  this->lcd->printLong(message);
  this->message = message;
  this->timer = timer;
  this->percentage = 0;
  this->mode = LOADING_BAR;
}

void LcdTask::init(int period) {
  Task::init(period);
}

void LcdTask::tick() {
  switch (this->mode) {
    case PRINT:
      if (!this->lcd->getPrintStatus()) {
        this->lcd->printLong(message);
      }
      break;
    case LOADING_BAR:
      if (this->timer->getTime() >= this->percentage*1000) {
        this->percentage++;
        this->lcd->printText("#", this->percentage, 1);
      }
      break;
  }
}