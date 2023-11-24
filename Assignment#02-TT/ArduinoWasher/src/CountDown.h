#ifndef __ARDUINO_TIMER__
#define __ARDUINO_TIMER__

#include "Task.h"
#include <arduino-timer.h>

class CountDown : public Task {
private:
  Timer<> timer;
  unsigned long waitTime;
  Timer<>::handler_t h;
  void *opaque;
public:
  CountDown(unsigned long waitTime, Timer<>::handler_t h, void *opaque);
  void init(int period);
  void tick();
  void start();
  void reset();
};

#endif