#include "ProceedingHandler.h"

void ProceedingHandler::initTasks(ChangeFun f) {
  this->lcd = new LcdTask("Proceed to the Washing Area");
  this->led = new LedTask(PROC_LED_PIN, BLINK);
  this->gate = new GateTask(PROC_GATE_PIN, OPEN);
  this->lcd->init(150);
  this->led->init(200);
  this->gate->init(150);
  tasksHandled[0] = lcd;
  tasksHandled[1] = led;
  tasksHandled[2] = gate;
}

void ProceedingHandler::setChangeState(bool state) {
  //this->gate->setChangeState(state);
}

int ProceedingHandler::getTasksCount() {
  return PROCEEDING_TASKS_COUNT;
}

