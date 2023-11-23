#include "WelcomeHandler.h"

void WelcomeHandler::initTasks(ChangeFun f){
  this->led = new LedTask(LED_PIN);
  this->led->init(150);
  this->lcd = new LcdTask();
  this->lcd->init(150);
  tasksHandled[0] = led;
  tasksHandled[1] = lcd;
}

void WelcomeHandler::setChangeState(bool state) {

}

void WelcomeHandler::afterChangeState() { }