#ifndef __WASHING_HANDLER__
#define __WASHING_HANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "LcdTask.h"
#include "CountDown.h"

#define WASH_TASKS_COUNT 3
#define WASH_TIME 16*1000

class WashingHandler : public TaskHandler{
private:
  LedTask *led;
  LcdTask* lcd;
  CountDown* timer;
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif