#include "LeavedHandler.h"

void LeavedHandler::initTasks() {
  Serial.println("LeavedHandler tasks...");
  delay(100);
  this->led1 = new LedTask(this->hw->green1, OFF);
  this->led1->init(150);
  this->led3 = new LedTask(this->hw->green3, OFF);
  this->led3->init(150);
  this->gate = new GateTask(this->hw->gate, CLOSE);
  this->gate->init(150);
  this->timer = new CountDown(N5, this->changeFun);
  this->timer->init(150);
  this->tasksHandled[0] = led1;
  this->tasksHandled[1] = led3;
  this->tasksHandled[2] = gate;
  this->tasksHandled[3] = timer;
  Serial.println("LeavedHandler tasks initialized!");
  delay(1000);
}

void LeavedHandler::setChangeState(bool state) {
  if (state) {
    this->timer->start();
  } else {
    this->timer->reset();
  }
}

int LeavedHandler::getTasksCount() {
  return LEAVED_TASKS_COUNT;
}