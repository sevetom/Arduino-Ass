#include "GateTask.h"

GateTask::GateTask(int pin, gateMode mode) {
  this->gate = new Gate(pin);
  this->mode = mode;
  this->isOpen = false;
  this->currentTime = 0;
}

void GateTask::init(int period) {
  Task::init(period);
}

void GateTask::tick() {
  switch (this->mode) {
    case OPEN:
      if (this->currentTime == 0) {
        this->gate->open();
      }
      if (this->currentTime >= OPEN_TIME) {
        this->gate->stop();
        this->currentTime = 0;
      }
      break;
    case CLOSE:
      if (this->currentTime == 0) {
        this->gate->close();
      }
      if (this->currentTime >= CLOSE_TIME) {
          this->gate->stop();
          this->currentTime = 0;
      }
      break;
  }
  currentTime += Task::myPeriod;
}