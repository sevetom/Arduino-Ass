#ifndef __COUNT_DOWN__
#define __COUNT_DOWN__

#include "Task.h"
#include <Arduino.h>

class CountDown : public Task {
private:
  long waitTime;
  long currentTime;
  bool isRunning;
  using InterruptFun = void (*)(void);
  InterruptFun interruptFunction;
public:
  CountDown(long time, InterruptFun f);
  void init(int period);
  void tick();
  void start();
  void reset();
  long getTime();
  void restart();
};

#endif