#ifndef __LED_TASK__
#define __LED_TASK__

#include "Task.h"
#include <Arduino.h>
#include "Led.h"

class LedTask : public Task {
private:
  Led* led;
public:
  LedTask(int pin);
  void init(int period);
  void tick();
};

#endif