#include "WelcomeHandler.h"

void WelcomeHandler::initTasks(ChangeFun f){
  this->led = new LedTask(WELC_LED_PIN, ON);
  this->led->init(150);
  this->lcd = new LcdTask("Welcome");
  this->lcd->init(150);
  this->timer = new CountDown(N1, f);
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