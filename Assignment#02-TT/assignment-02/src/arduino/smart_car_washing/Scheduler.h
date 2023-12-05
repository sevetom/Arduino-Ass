#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 25

/**
 * Scheduler that handles the tasks
*/
class Scheduler {
  
  unsigned long basePeriod;
  int nTasks;
  // the start and end of the window in which the current tasks will be executed
  int startWindow;
  int endWindow;
  Task* taskList[MAX_TASKS];
  // the time when the last loop has been executed
  unsigned long lastLoopTime;

public:
  /**
   * Initializes the scheduler
   * @param basePeriod The base period of the scheduler
  */
  void init(unsigned long basePeriod);  
  /**
   * Adds a task to the scheduler
   * @param task The task to add
   * @return True if the task has been added, false otherwise
  */
  bool addTask(Task* task);  
  /**
   * Shifts the tasks window of the scheduler
   * @param shift The amount of time to shift the window
  */
  void shiftTasks(int shift);
  /**
   * Resets the window of the scheduler
   * and restarts all the tasks
  */
  void resetWindow();
  /**
   * Updates the scheduler and its tasks
  */
  void schedule();
};

#endif
