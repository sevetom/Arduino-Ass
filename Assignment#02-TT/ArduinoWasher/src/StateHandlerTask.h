#ifndef __STATEHANDLERTASK__
#define __STATEHANDLERTASK__

#include <stdlib.h>
#include <EnableInterrupt.h>
#include "Task.h"
#include "Scheduler.h"
#include "TaskHandler.h"

class StateHandlerTask : public Task {
private:
    int currentHandler;
    Scheduler* sched;
    TaskHandler** taskHandlers;
    int handlerCount;
    bool change;

public:
    StateHandlerTask(Scheduler* sched, TaskHandler** taskHandlers);
    void changeState();
    void init(int period);  
    void tick();
    void changeTasks();
    void insertTasks(Task** list);
};

#endif