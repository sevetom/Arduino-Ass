#include <Arduino.h>
#include "Scheduler.h"
#include "StateHandlerTask.h"
#include "TaskHandler.h"
#include "SleepHandler.h"
#include "WelcomeHandler.h"
#include "ProceedingHandler.h"
#include "EnteredHandler.h"
#include "WashingHandler.h"
#include "ExitingHandler.h"
#include "LeavedHandler.h"

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

void insertTasks(Task** list);

Scheduler* sched;
TaskHandler* taskHandlers[TASK_HANDLERS];
StateHandlerTask* stateHandlerTask;

void setup() {
	Serial.begin(9600);
  sched = new Scheduler();
  sched->init(50);
  stateHandlerTask = new StateHandlerTask(sched, taskHandlers, TASK_HANDLERS);
  stateHandlerTask->init(150);
  sched->addTask(stateHandlerTask);
  taskHandlers[SLEEPING] = new SleepHandler();
  taskHandlers[WELCOME] = new WelcomeHandler();
  taskHandlers[PROCEEDING] = new ProceedingHandler();
  //taskHandlers[ENTERED] = new EnteredHandler();
  //taskHandlers[WASHING] = new WashingHandler();
  //taskHandlers[EXITING] = new ExitingHandler();
  //taskHandlers[LEAVED] = new LeavedHandler();
  for (int i = 0; i < TASK_HANDLERS - 4; i++){
    Serial.println("Inserting tasks: " + String(i));
    taskHandlers[i]->initTasks([](){ stateHandlerTask->changeState(); });
    insertTasks(taskHandlers[i]->getTasks());
  }
  stateHandlerTask->changeTasks();
}

void loop() {
	sched->schedule();
}

void insertTasks(Task** list) {
  int cur = 0;
  while(list[cur] != NULL) {
    sched->addTask(list[cur]);
    cur++;
  }
}