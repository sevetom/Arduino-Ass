#ifndef __STATEHANDLERTASK__
#define __STATEHANDLERTASK__

#include "Scheduler.h"
#include "TaskHandler.h"
#include <Arduino.h>

class StateHandlerTask : public Task {
private:
    int currentHandler;
    Scheduler* sched;
    TaskHandler** taskHandlers;
    int handlerCount;
    bool change;

public:
    StateHandlerTask(Scheduler* sched, TaskHandler** taskHandlers, int handlerCount);
    void changeState();
    void init(int period);  
    void tick();
    void changeTasks();
    bool getChangeState() { return this->change; }
};

#endif