#include "CountDown.h"

CountDown::CountDown(long time, InterruptFun f) {
  this->waitTime = time;
  this->interruptFunction = f;
  this->currentTime = 0;
}

void CountDown::init(int period) {
  Task::init(period);
}

void CountDown::tick() {
  if (this->isRunning) {
    this->currentTime += this->myPeriod + this->timeElapsed;
    if (this->currentTime >= this->waitTime) {
      this->reset();
      this->interruptFunction();
    }
  }
}

void CountDown::start() {
  this->isRunning = true;
}

void CountDown::reset() {
  this->isRunning = false;
  this->currentTime = 0;
}