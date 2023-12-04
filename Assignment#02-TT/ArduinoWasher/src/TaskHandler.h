#ifndef __TASK_HANDLER__
#define __TASK_HANDLER__
#define MAX_HANDLER_TASKS 5

#include "Task.h"
#include <stdio.h>
#include "WashingComponents.h"

/**
 * Class to handle a group of tasks
*/
class TaskHandler {

protected:
  using ChangeFunction = void(*)();
  ChangeFunction changeFun;
  Task* tasksHandled[MAX_HANDLER_TASKS];
  WashingComponents* hw;

public:
  /**
   * Initialize the tasks handled by this handler
  */
  virtual void initTasks() {
    for (int i = 0; i < MAX_HANDLER_TASKS; i++) {
      this->tasksHandled[i] = NULL;
    }
  }

  /**
   * Returns the tasks handled by this handler
   * @return The tasks handled by this handler
  */
  virtual Task** getTasks() {
    return this->tasksHandled;
  }

  /**
   * Sets the function to call when the state of the handler changes
   * and the hardware components to use
   * @param f The function to call when the state of the handler changes
   * @param hw The hardware components to use
  */
  virtual void setHandler(ChangeFunction f, WashingComponents* hw) {
    this->changeFun = f;
    this->hw = hw;
  }

  /**
   * Returns the number of tasks handled by this handler
   * @return The number of tasks handled by this handler
  */
  virtual int getTasksCount() = 0;

  /**
   * Sets the change condition of the handler
   * @param state true if the handler should change to the next state, false otherwise
  */
  virtual void setChangeState(bool state) = 0;
};

#endif