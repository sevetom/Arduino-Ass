#ifndef __PROCEEDING_HANDLER__
#define __PROCEEDING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "GateTask.h"

#define PROCEEDING_TASKS_COUNT 3
#define PROC_LED_PIN 13
#define PROC_GATE_PIN 4

class ProceedingHandler : public TaskHandler{
private:
  LcdTask* lcd;
  LedTask* led;
  GateTask* gate;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  int getTasksCount();
};

#endif