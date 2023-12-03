#ifndef __PROCEEDING_HANDLER__
#define __PROCEEDING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "GateTask.h"
#include "SonarTask.h"

#define PROCEEDING_TASKS_COUNT 4

class ProceedingHandler : public TaskHandler{
private:
  LcdTask* lcd;
  LedTask* led;
  GateTask* gate;
  SonarTask* sonar;
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif