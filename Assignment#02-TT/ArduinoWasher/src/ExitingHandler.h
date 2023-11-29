#ifndef __EXITING_HANDLER__
#define __EXITING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "SonarTask.h"

#define EXT_TASKS_COUNT 4

class ExitingHandler : public TaskHandler {
private:
  LcdTask* lcd;
  LedTask* greenLed;
  LedTask* redLed;
  SonarTask* sonar;
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif