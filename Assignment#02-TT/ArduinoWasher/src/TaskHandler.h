#ifndef __TASK_HANDLER__
#define __TASK_HANDLER__
#define MAX_TASKS 50

#include "Task.h"
#include <stdio.h>

class TaskHandler {

protected:
  using ChangeFun = void(*)();
  ChangeFun changeFun;
  Task* tasksHandled[MAX_TASKS];

public:
  virtual void initTasks(ChangeFun f) {
    this->changeFun = f;
    for (int i = 0; i < MAX_TASKS; i++) {
      tasksHandled[i] = NULL;
    }
  }

  virtual Task** getTasks() {
    return tasksHandled;
  }

  virtual void setChangeState(bool state) = 0;
};

#endif