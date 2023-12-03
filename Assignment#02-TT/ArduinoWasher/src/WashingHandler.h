#ifndef __WASHING_HANDLER__
#define __WASHING_HANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "LcdTask.h"
#include "CountDown.h"
#include "TempTask.h"

#define WASH_TASKS_COUNT 4
#define WASH_TIME 16*1000

class WashingHandler : public TaskHandler{
private:
  LedTask *led; // 12
  LcdTask* lcd; // 13
  CountDown* timer; // 14
  TempTask* tempSensor; // 15
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif