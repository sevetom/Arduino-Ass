#include "SleepHandler.h"

void SleepHandler::initTasks(StateHandlerTask* stateHandlerTask){
  TaskHandler::stateHandlerTask = stateHandlerTask;
  this->pir = new Pir(PIR_PIN);
  this->pir->init();
  sleep = new SleepTask();
  sleep->init(150);
  tasksHandled[0] = sleep;
}

void SleepHandler::setChangeState(bool state) {
  if (state){
    this->pir->enInterrupt([this](){
      TaskHandler::stateHandlerTask->changeState();
    });
  } else {
    this->pir->disInterrupt();
  }
}

void SleepHandler::afterChangeState() {
  sleep_disable();
  Serial.flush();
}