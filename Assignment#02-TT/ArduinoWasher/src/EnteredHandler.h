#ifndef __ENTERED_HANDLER__
#define __ENTERED_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "GateTask.h"
#include "Button.h"

#define ENT_TASKS_COUNT 3

class EnteredHandler : public TaskHandler {
private:
  LcdTask* lcd; // 9
  LedTask* led; // 10
  GateTask* gate; // 11
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif