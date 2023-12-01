#include "SleepHandler.h"

void SleepHandler::initTasks(){
  this->sleep = new SleepTask();
  this->sleep->init(150);
  this->tasksHandled[0] = sleep;
}

void SleepHandler::setChangeState(bool state) {
  this->hw->pir->setInterrupt(this->changeFun, state);
}

int SleepHandler::getTasksCount() {
  return SLEEP_TASKS_COUNT;
}