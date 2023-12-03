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
  Serial.println("Timer tick");
  delay(100);
  if (this->isRunning) {
    this->currentTime += this->myPeriod + this->timeElapsed;
    if (this->currentTime >= this->waitTime) {
      Serial.println("Timer tick interrupt ENTROOOOOO");
      this->reset();
      this->interruptFunction();
    }
  }
  Serial.println("Timer tick end " + String(this->currentTime));
  delay(100);
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