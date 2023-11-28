#ifndef __LED_TASK__
#define __LED_TASK__

#include "Task.h"
#include "Led.h"

typedef enum {
  ON,
  OFF,
  BLINK
} ledMode;

class LedTask : public Task {
private:
  Led* led;
  ledMode mode;
public:
  LedTask(int pin, ledMode mode);
  void init(int period);
  void tick();
};

#endif