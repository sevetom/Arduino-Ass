#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 50

class Scheduler {
  
  long basePeriod;
  int nTasks;
  int startWindow;
  int endWindow;
  Task* taskList[MAX_TASKS];

public:
  void init(long basePeriod);  
  bool addTask(Task* task);  
  void shiftTasks(int shift);
  void schedule();
  void printTasks();
};

#endif
