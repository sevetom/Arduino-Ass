#ifndef __WELCOME_HANDLER__
#define __WELCOME_HANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "LcdTask.h"
#include "CountDown.h"

#define WELCOME_TASKS_COUNT 3
#define N1 5000

class WelcomeHandler : public TaskHandler {
private:
  LedTask* led;
  LcdTask* lcd;
  CountDown* timer;
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif