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
  if (this->cycles >= GATE_CYCLES) {
    this->cycles = -1;
    this->gate->stop();
    this->gate->off();
  }
}

void GateTask::restart() {
  this->timeElapsed = 0;
  this->cycles = 0;
}