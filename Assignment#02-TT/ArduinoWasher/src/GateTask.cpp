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
  Serial.println("cycles1: " + String(this->cycles));
  if (this->cycles == 0) {
    this->gate->on();
    Serial.println("mode: " + String(this->mode));
    switch (this->mode) {
      case OPEN:
        this->gate->open();
        break;
      case CLOSE:
        this->gate->close();
        break;
    }
  }
  this->cycles = this->cycles != -1 ? this->cycles + 1 : 0;
  Serial.println("cycles2: " + String(this->cycles));
  if (this->cycles >= GATE_CYCLES) {
    this->cycles = -1;
    this->gate->stop();
    this->gate->off();
  }
}