#ifndef __SLEEP_HANDLER__
#define __SLEEP_HANDLER__

#include "StateHandlerTask.h"
#include "SleepTask.h"
#include "Pir.h"

#define SLEEP_TASKS_COUNT 1

/**
 * Class to handle the sleep state when no car is around
*/
class SleepHandler : public TaskHandler {
private:
  SleepTask* sleep; // 1
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif