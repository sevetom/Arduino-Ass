#include "WelcomeHandler.h"

void WelcomeHandler::initTasks(){
  this->led = new LedTask(this->hw->green1, ON);
  this->led->init(150);
  this->lcd = new LcdTask(this->hw->lcd, "Welcome");
  this->lcd->init(150);
  this->timer = new CountDown(N1, this->changeFun);
  this->timer->init(150);
  this->tasksHandled[0] = led;
  this->tasksHandled[1] = lcd;
  this->tasksHandled[2] = timer;
}

void WelcomeHandler::setChangeState(bool state) {
  if (state) {
    this->timer->start();
  } else {
    this->timer->reset();
  }
}

int WelcomeHandler::getTasksCount() {
  return WELCOME_TASKS_COUNT;
}