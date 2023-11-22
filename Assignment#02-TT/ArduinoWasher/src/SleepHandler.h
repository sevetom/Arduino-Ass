#ifndef __SLEEP_HANDLER__
#define __SLEEP_HANDLER__

#include "TaskHandler.h"
#include "SleepTask.h"
#include "Pir.h"

#define PIR_PIN 2

class SleepHandler : public TaskHandler {
private:
  Pir* pir;
  SleepTask* sleep;
public:
  void initTasks(StateHandlerTask* stateHandlerTask);
  void setChangeState(bool state);
  void afterChangeState();
};

#endif