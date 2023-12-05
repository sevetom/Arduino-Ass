#ifndef __EXITING_HANDLER__
#define __EXITING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "SonarTask.h"
#include "GateTask.h"

#define EXT_TASKS_COUNT 5

/**
 * Task handler that handles the tasks when the car is exiting the washing machine
*/
class ExitingHandler : public TaskHandler {
private:
  LcdTask* lcd; // 16
  LedTask* greenLed; // 17
  LedTask* redLed; // 18
  SonarTask* sonar; // 19
  GateTask* gate; // 20
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif