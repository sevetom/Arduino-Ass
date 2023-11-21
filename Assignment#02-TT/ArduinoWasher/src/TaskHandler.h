#ifndef __TASK_HANDLER__
#define __TASK_HANDLER__
#define MAX_TASKS 50

#include "Task.h"

class TaskHandler {

protected:
  Task* tasksHandled[MAX_TASKS];

public:
  virtual void initTasks() {
    for (int i = 0; i < MAX_TASKS; i++) {
      tasksHandled[i] = NULL;
    }
  }

  virtual Task** getTasks() {
    return tasksHandled;
  }

  virtual int getInterruptPin() {
    return 0;
  }

  virtual void afterInterrupt() = 0;
};

#endif