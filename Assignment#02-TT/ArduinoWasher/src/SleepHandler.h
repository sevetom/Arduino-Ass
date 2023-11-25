#ifndef __SLEEP_HANDLER__
#define __SLEEP_HANDLER__

#include "StateHandlerTask.h"
#include "SleepTask.h"
#include "Pir.h"

#define PIR_PIN 2

class SleepHandler : public TaskHandler {
private:
  Pir* pir;
  SleepTask* sleep;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  void afterChangeState();
};

#endif