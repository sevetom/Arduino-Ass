#ifndef __TASK_HANDLER__
#define __TASK_HANDLER__
#define MAX_TASKS 50

#include "Task.h"
#include "StateHandlerTask.h"

class TaskHandler {

protected:
  StateHandlerTask* stateHandlerTask;
  Task* tasksHandled[MAX_TASKS];

public:
  virtual void initTasks(StateHandlerTask* stateHandlerTask) {
    this->stateHandlerTask = stateHandlerTask;
    for (int i = 0; i < MAX_TASKS; i++) {
      tasksHandled[i] = NULL;
    }
  }

  virtual Task** getTasks() {
    return tasksHandled;
  }

  virtual void setChangeState(bool state) = 0;

  virtual void afterChangeState() = 0;
};

#endif