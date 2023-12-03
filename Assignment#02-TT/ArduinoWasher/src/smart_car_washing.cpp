#include <Arduino.h>
#include "WashingComponents.h"
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
#include "TempSensor.h"

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
WashingComponents* hw;
TaskHandler* taskHandlers[TASK_HANDLERS];
StateHandlerTask* stateHandlerTask;

void setup() {
	Serial.begin(9600);
  hw = new WashingComponents();
  sched = new Scheduler();
  sched->init(50);
  stateHandlerTask = new StateHandlerTask(sched, taskHandlers, TASK_HANDLERS);
  stateHandlerTask->init(150);
  sched->addTask(stateHandlerTask);
  taskHandlers[SLEEPING] = new SleepHandler();
  //taskHandlers[WELCOME] = new WelcomeHandler();
  //taskHandlers[PROCEEDING] = new ProceedingHandler();
  //taskHandlers[ENTERED] = new EnteredHandler();
  //taskHandlers[WASHING] = new WashingHandler();
  //taskHandlers[EXITING] = new ExitingHandler();
  taskHandlers[LEAVED-5] = new LeavedHandler();
  for (int i = 0; i < TASK_HANDLERS-5; i++){
    taskHandlers[i]->setHandler([](){ stateHandlerTask->changeState(); }, hw);
    taskHandlers[i]->initTasks();
    insertTasks(taskHandlers[i]->getTasks());
    delay(100);
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