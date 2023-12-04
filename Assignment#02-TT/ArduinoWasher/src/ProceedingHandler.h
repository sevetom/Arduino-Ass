#ifndef __PROCEEDING_HANDLER__
#define __PROCEEDING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "GateTask.h"
#include "SonarTask.h"

#define PROCEEDING_TASKS_COUNT 4

/**
 * Task handler that handles the tasks when the car is proceeding into the washing machine
*/
class ProceedingHandler : public TaskHandler{
private:
  LcdTask* lcd; // 5
  LedTask* led; // 6
  GateTask* gate; // 7
  SonarTask* sonar; // 8
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif