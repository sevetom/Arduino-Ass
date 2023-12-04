#include "CountDown.h"

CountDown::CountDown(long time, InterruptFun f) {
  this->waitTime = time;
  this->interruptFunction = f;
  this->currentTime = 0;
  this->isRunning = false;
}

void CountDown::init(int period) {
  Task::init(period);
}

void CountDown::tick() {
  /**
   * Adds the time elapsed since the last tick to the current time
   * and calls the interrupt function if the time is up
  */
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

long CountDown::getTime() {
  return this->currentTime;
}

void CountDown::restart() {
  this->timeElapsed = 0;
  this->reset();
}