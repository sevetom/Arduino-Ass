#include "CountDown.h"

CountDown::CountDown(unsigned long waitTime, Timer<>::handler_t h, void *opaque) {
  this->waitTime = waitTime;
  this->h = h;
  this->opaque = opaque;
  timer.every(waitTime, h, opaque);
}

void CountDown::init(int period) {
  Task::init(period);
}

void CountDown::tick() {
  timer.tick();
}

void CountDown::start() {
  timer.in(this->waitTime, this->h, this->opaque);
}

void CountDown::reset() {
  timer.cancel();
}