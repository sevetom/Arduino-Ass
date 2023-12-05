#ifndef __GATE_TASK__
#define __GATE_TASK__

// Cycles needed to open and close the gate
#define OPEN_CYCLES 5
#define CLOSE_CYCLES 6

#include "Task.h"
#include "Gate.h"

typedef enum {
  OPEN,
  CLOSE
} gateMode;

/**
 * Task that opens and closes the gate
*/
class GateTask : public Task {
private:
  Gate* gate;
  gateMode mode;
  // number of cycles done since opening/closing
  int cycles;
  using InterruptFun = void (*)();
  InterruptFun interruptFunction;
public:
  /**
   * Initialize a gate task
   * @param gate The gate to open/close
   * @param mode The mode of the gate (OPEN/CLOSE)
  */
  GateTask(Gate* gate, gateMode mode);
  void init(int period);
  void tick();
  void restart();
  /**
   * If needed a function can be called when the gate is opened/closed
   * @param f The function to call
   * @param state If true the function should be called
  */
  void setInterruptFun(InterruptFun f, bool state);
};
#endif