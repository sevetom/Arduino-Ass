#include "SleepHandler.h"

void SleepHandler::initTasks(ChangeFun f){
  TaskHandler::changeFun = f;
  this->pir = new Pir(PIR_PIN);
  this->pir->init();
  sleep = new SleepTask();
  sleep->init(150);
  tasksHandled[0] = sleep;
}

void SleepHandler::setChangeState(bool state) {
  this->pir->setInterrupt(TaskHandler::changeFun, state);
}

int SleepHandler::getTasksCount() {
  return SLEEP_TASKS_COUNT;
}