#ifndef __GATE_TASK__
#define __GATE_TASK__

#define OPEN_CYCLES 6
#define CLOSE_CYCLES 11

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
  using InterruptFun = void (*)();
  InterruptFun interruptFunction;
public:
  GateTask(Gate* gate, gateMode mode);
  void init(int period);
  void tick();
  void restart();
  void setInterruptFun(InterruptFun f, bool state);
};
#endif