#ifndef __LEAVEDHANDLER__
#define __LEAVEDHANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "GateTask.h"
#include "CountDown.h"

#define LEAVED_TASKS_COUNT 4
#define N5 5*1000

class LeavedHandler : public TaskHandler {
private:
  LedTask* led1;
  LedTask* led3;
  GateTask* gate; //13 (con -3)
  CountDown* timer;
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif