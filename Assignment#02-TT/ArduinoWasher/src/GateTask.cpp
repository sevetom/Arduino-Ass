#include "GateTask.h"

GateTask::GateTask(int pin, gateMode mode) {
  this->gate = new Gate(pin);
  this->mode = mode;
  this->cycles = 0;
}

void GateTask::init(int period) {
  Task::init(period);
}

void GateTask::tick() {
  Serial.println("cycles1: " + this->cycles);
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
  this->cycles++;
  Serial.println("cycles2: " + this->cycles);
  if (this->cycles >= GATE_CYCLES) {
    this->cycles = 0;
    this->gate->stop();
    this->gate->off();
  }
}