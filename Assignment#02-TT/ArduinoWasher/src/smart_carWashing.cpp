#include <Arduino.h>
#include <EnableInterrupt.h>
#include "Scheduler.h"
#include "StateHandlerTask.h"
#include "TaskHandler.h"
#include "SleepHandler.h"
#include "WelcomeHandler.h"

#define TASK_HANDLERS 7

typedef enum {
  SLEEPING,
  WELCOME,
  PROCEEDING,
  ENTERED,
  WASHING,
  EXITING,
  LEAVED
} taskHandlerType;

Scheduler sched;
TaskHandler* taskHandlers[TASK_HANDLERS];
StateHandlerTask* stateHandlerTask;

void setup() {
	Serial.begin(9600);
  sched.init(50);
  stateHandlerTask = new StateHandlerTask(&sched, taskHandlers);
  stateHandlerTask->init(50);
  sched.addTask(stateHandlerTask);
  taskHandlers[SLEEPING] = new SleepHandler();
  taskHandlers[WELCOME] = new WelcomeHandler();
  /*
  taskHandlers[PROCEEDING] = new ProceedingHandler();
  taskHandlers[ENTERED] = new EnteredHandler();
  taskHandlers[WASHING] = new WashingHandler();
  taskHandlers[EXITING] = new ExitingHandler();
  taskHandlers[LEAVED] = new LeavedHandler();
  */
  for (int i = 0; i < TASK_HANDLERS-5; i++){
    taskHandlers[i]->initTasks(stateHandlerTask);
  }
  stateHandlerTask->changeTasks();
}

void loop() {
	sched.schedule();
}