#include "LeavedHandler.h"

void LeavedHandler::initTasks() {
  this->gate = new GateTask(this->hw->gate, CLOSE);
  this->gate->init(150);
  this->led1 = new LedTask(this->hw->green1, OFF);
  this->led1->init(150);
  this->led3 = new LedTask(this->hw->green3, OFF);
  this->led3->init(150);
  this->tasksHandled[0] = gate;
  this->tasksHandled[1] = led3;
  this->tasksHandled[2] = led1;
}

void LeavedHandler::setChangeState(bool state) {
  this->gate->setInterruptFun(this->changeFun, state);
}

int LeavedHandler::getTasksCount() {
  return LEAVED_TASKS_COUNT;
}