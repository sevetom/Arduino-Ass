#include "GateTask.h"

GateTask::GateTask(Gate* gate, gateMode mode) {
  this->gate = gate;
  this->mode = mode;
  this->cycles = 0;
}

void GateTask::init(int period) {
  Task::init(period);
}

void GateTask::tick() {
  Serial.println("Gate tick");
  delay(10);
  if (this->cycles == 0) {
    this->gate->on();
    switch (this->mode) {
      case OPEN:
        this->gate->open();
        break;
      case CLOSE:
        this->gate->close();
        break;
    }
  }
  this->cycles += this->cycles != -1 ? 1 : 0;
  if (this->cycles >= (this->mode == OPEN ? OPEN_CYCLES : CLOSE_CYCLES)) {
    this->cycles = -1;
    this->gate->stop();
    this->gate->off();
  }
}

void GateTask::restart() {
  this->timeElapsed = 0;
  this->cycles = 0;
}