#include "ProceedingHandler.h"

void ProceedingHandler::initTasks(ChangeFun f) {
  this->lcd = new LcdTask("Proceed to the \n Washing Area");
  this->lcd->init(150);
  this->led = new LedTask(PROC_LED_PIN, BLINK);
  this->led->init(300);
  this->gate = new GateTask(PROC_GATE_PIN, OPEN);
  this->gate->init(150);
  this->sonar = new SonarTask(PROC_TRIG_PIN, PROC_ECHO_PIN, f, MIN);
  this->sonar->init(150);
  this->tasksHandled[0] = lcd;
  this->tasksHandled[1] = led;
  this->tasksHandled[2] = gate;
  this->tasksHandled[3] = sonar;
}

void ProceedingHandler::setChangeState(bool state) {
  this->sonar->setReading(state);
}

int ProceedingHandler::getTasksCount() {
  return PROCEEDING_TASKS_COUNT;
}

