#ifndef __LEAVEDHANDLER__
#define __LEAVEDHANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "GateTask.h"
#include "CountDown.h"

#define LEAVED_TASKS_COUNT 3
#define LEAVED_LED_PIN 12
#define LEAVED_GATE_PIN 5
#define N5 2

class LeavedHandler : public TaskHandler {
private:
  LedTask* led;
  GateTask* gate;
  CountDown* timer;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  int getTasksCount();
};

#endif