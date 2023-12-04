#ifndef __EXITING_HANDLER__
#define __EXITING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "SonarTask.h"
#include "GateTask.h"

#define EXT_TASKS_COUNT 5

class ExitingHandler : public TaskHandler {
private:
  LcdTask* lcd; // 17
  LedTask* greenLed; // 18
  LedTask* redLed; // 19
  SonarTask* sonar; // 20
  GateTask* gate; // 21
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif