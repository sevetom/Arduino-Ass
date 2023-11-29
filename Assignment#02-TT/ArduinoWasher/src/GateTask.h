#ifndef __GATE_TASK__
#define __GATE_TASK__

#define GATE_CYCLES 50

#include "Task.h"
#include "Gate.h"

typedef enum {
  OPEN,
  CLOSE
} gateMode;

class GateTask : public Task {
private:
  Gate* gate;
  gateMode mode;
  int cycles;
public:
  GateTask(int pin, gateMode mode);
  void init(int period);
  void tick();
};
#endif