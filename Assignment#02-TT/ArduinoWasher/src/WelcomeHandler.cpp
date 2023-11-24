#include "WelcomeHandler.h"

void WelcomeHandler::initTasks(ChangeFun f){
  this->led = new LedTask(LED_PIN);
  this->led->init(150);
  this->lcd = new LcdTask();
  this->lcd->init(150);
  this->timer = new CountDown(N1, [](void* fun) -> bool {
    ChangeFun changeFunction = reinterpret_cast<ChangeFun>(fun);
    changeFunction();
    return true;
  }, (void*)f);
  this->timer->init(0);
  tasksHandled[0] = led;
  tasksHandled[1] = lcd;
  tasksHandled[2] = timer;
}

void WelcomeHandler::setChangeState(bool state) {
  if (state) {
    this->timer->start();
  } else {
    this->timer->reset();
  }
}

void WelcomeHandler::afterChangeState() { }