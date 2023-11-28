#ifndef __GATE_TASK__
#define __GATE_TASK__

#define OPEN_TIME 500
#define CLOSE_TIME 560

#include "Task.h"
#include "Gate.h"

typedef enum {
  OPEN,
  CLOSE
} gateMode;

class GateTask : public Task {
private:
  Gate* gate;
  bool isOpen;
  gateMode mode;
  long currentTime;
public:
  GateTask(int pin, gateMode mode);
  void init(int period);
  void tick();
};
#endif