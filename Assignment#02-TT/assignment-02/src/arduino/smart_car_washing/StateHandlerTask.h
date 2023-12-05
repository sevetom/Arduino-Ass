#ifndef __STATEHANDLERTASK__
#define __STATEHANDLERTASK__

#include "Scheduler.h"
#include "TaskHandler.h"
#include <Arduino.h>

/**
 * Task that handles the state of the system
*/
class StateHandlerTask : public Task {
private:
  int currentHandler;
  Scheduler* sched;
  TaskHandler** taskHandlers;
  int handlerCount;
  bool change;
public:
  /**
   * Initialize a state handler task
   * @param sched The scheduler to use
   * @param taskHandlers The handlers to use
   * @param handlerCount The number of handlers
  */
  StateHandlerTask(Scheduler* sched, TaskHandler** taskHandlers, int handlerCount);
  /**
   * Tells the system that the next state should be used
  */
  void changeState();
  void init(int period);  
  void tick();
  /**
   * The current task handler is turned off and the next in line
   * is set to execution by the scheduler
   * If the line is at the end, the scheduler is reset
  */
  void changeTasks();
};

#endif