#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 25

class Scheduler {
  
  unsigned long basePeriod;
  int nTasks;
  int startWindow;
  int endWindow;
  Task* taskList[MAX_TASKS];
  unsigned long lastLoopTime;

public:
  void init(unsigned long basePeriod);  
  bool addTask(Task* task);  
  void shiftTasks(int shift);
  void resetWindow();
  void schedule();
};

#endif
