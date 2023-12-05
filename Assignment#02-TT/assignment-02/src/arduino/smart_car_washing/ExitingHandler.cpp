#include "ExitingHandler.h"

void ExitingHandler::initTasks() {
  this->lcd = new LcdTask(this->hw->lcd, "Washing complete, \n you can leave the area");
  this->lcd->init(150);
  this->greenLed = new LedTask(this->hw->green3, ON);
  this->greenLed->init(150);
  this->redLed = new LedTask(this->hw->red2, OFF);
  this->redLed->init(150);
  this->sonar = new SonarTask(this->hw->sonar,this->changeFun, MAX);
  this->sonar->init(150);
  this->gate = new GateTask(this->hw->gate, OPEN);
  this->gate->init(150);
  this->tasksHandled[0] = lcd;
  this->tasksHandled[1] = greenLed;
  this->tasksHandled[2] = redLed;
  this->tasksHandled[3] = sonar;
  this->tasksHandled[4] = gate;
}

void ExitingHandler::setChangeState(bool state) {
  this->sonar->setReading(state);
}

int ExitingHandler::getTasksCount() {
  return EXT_TASKS_COUNT;
}

