#ifndef __TASK_HANDLER__
#define __TASK_HANDLER__
#define MAX_HANDLER_TASKS 10

#include "Task.h"
#include <stdio.h>
#include "WashingComponents.h"

class TaskHandler {

protected:
  using ChangeFun = void(*)();
  ChangeFun changeFun;
  Task* tasksHandled[MAX_HANDLER_TASKS];
  WashingComponents* hw;

public:
  virtual void initTasks() {
    for (int i = 0; i < MAX_HANDLER_TASKS; i++) {
      this->tasksHandled[i] = NULL;
    }
  }

  virtual Task** getTasks() {
    return this->tasksHandled;
  }

  virtual void setHandler(ChangeFun f, WashingComponents* hw) {
    this->changeFun = f;
    this->hw = hw;
  }

  virtual int getTasksCount() = 0;

  virtual void setChangeState(bool state) = 0;
};

#endif