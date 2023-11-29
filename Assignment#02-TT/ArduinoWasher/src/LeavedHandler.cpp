#include "LeavedHandler.h"

void LeavedHandler::initTasks(ChangeFun f) {
  this->led = new LedTask(LEAVED_LED_PIN, OFF);
  this->led->init(150);
  this->gate = new GateTask(LEAVED_GATE_PIN, CLOSE);
  this->gate->init(150);
  this->timer = new CountDown(N5, f);
  this->timer->init(150);
  this->tasksHandled[0] = led;
  this->tasksHandled[1] = gate;
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