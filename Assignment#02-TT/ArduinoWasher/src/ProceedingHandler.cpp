#include "ProceedingHandler.h"

void ProceedingHandler::initTasks() {
  Serial.println("ProceedingHandler tasks...");
  this->lcd = new LcdTask(this->hw->lcd, "Proceed to the \n Washing Area");
  this->lcd->init(150);
  this->led = new LedTask(this->hw->green1, BLINK);
  this->led->init(100);
  this->gate = new GateTask(this->hw->gate, OPEN);
  this->gate->init(150);
  this->sonar = new SonarTask(this->hw->sonar, this->changeFun, MIN);
  this->sonar->init(150);
  this->tasksHandled[0] = lcd;
  this->tasksHandled[1] = led;
  this->tasksHandled[2] = gate;
  this->tasksHandled[3] = sonar;
  Serial.println("ProceedingHandler tasks initialized!");
}

void ProceedingHandler::setChangeState(bool state) {
  this->sonar->setReading(state);
  Serial.println("ProceedingHandler Change State: " + String(state));
}

int ProceedingHandler::getTasksCount() {
  return PROCEEDING_TASKS_COUNT;
}

