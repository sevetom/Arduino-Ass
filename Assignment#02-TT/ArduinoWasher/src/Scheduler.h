#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 50

class Scheduler {
  
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  

public:
  void init(int basePeriod);  
  bool addTask(Task* task);  
  void removeTasks(Task** tasks);
  void schedule();
};

#endif
