#ifndef __SLEEP_HANDLER__
#define __SLEEP_HANDLER__

#include "StateHandlerTask.h"
#include "SleepTask.h"
#include "Pir.h"

#define SLEEP_TASKS_COUNT 1
#define PIR_PIN 2

class SleepHandler : public TaskHandler {
private:
  Pir* pir;
  SleepTask* sleep;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  int getTasksCount();
};

#endif