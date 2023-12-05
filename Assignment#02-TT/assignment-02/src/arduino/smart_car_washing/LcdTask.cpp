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
  /**
   * First prints the message on the LCD display
   * if not already printed
  */
  if (!this->printStatus) {
    this->lcd->printLong(this->message);
    this->printStatus = true;
  }
  /**
   * Then, if needed, prints the loading bar on the LCD display
   * if a second has passed
  */
  if (this->mode == LOADING_BAR && this->timer->getTime() >= this->percentage*1000) {
    this->lcd->printText("#", this->percentage, 1);
    this->percentage++;
  }
}

void LcdTask::restart() {
  this->timeElapsed = 0;
  this->percentage = 0;
  this->printStatus = false;
  this->lcd->clear();
  if (this->mode == LOADING_BAR) {
    this->timer->resetTime();
  }
}

LcdDisplay* LcdTask::getLcd() {
  return this->lcd;
}