#include "ExitingHandler.h"

void ExitingHandler::initTasks(ChangeFun f) {
  this->lcd = new LcdTask("Washing complete, \n you can leave the area");
  this->lcd->init(150);
  this->greenLed = new LedTask(EXT_GREEN_LED_PIN, ON);
  this->greenLed->init(150);
  this->redLed = new LedTask(EXT_RED_LED_PIN, OFF);
  this->redLed->init(150);
  this->sonar = new SonarTask(EXT_SONAR_TRIG_PIN, EXT_SONAR_ECHO_PIN, f, MAX);
  this->sonar->init(150);
  this->tasksHandled[0] = lcd;
  this->tasksHandled[1] = greenLed;
  this->tasksHandled[2] = redLed;
  this->tasksHandled[3] = sonar;
}

void ExitingHandler::setChangeState(bool state) {
  this->sonar->setReading(state);
}

int ExitingHandler::getTasksCount() {
  return EXT_TASKS_COUNT;
}

