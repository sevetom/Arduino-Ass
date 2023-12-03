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
  //taskHandlers[SLEEPING] = new SleepHandler();
  //taskHandlers[WELCOME-1] = new WelcomeHandler();
  //taskHandlers[PROCEEDING-2] = new ProceedingHandler();
  //taskHandlers[ENTERED-3] = new EnteredHandler();
  taskHandlers[WASHING-4] = new WashingHandler();
  taskHandlers[EXITING-4] = new ExitingHandler();
  taskHandlers[LEAVED-4] = new LeavedHandler();
  for (int i = 0; i < TASK_HANDLERS-4; i++){
    Serial.println("Inserting tasks: " + String(i));
    taskHandlers[i]->setHandler([](){ stateHandlerTask->changeState(); }, hw);
    taskHandlers[i]->initTasks();
    insertTasks(taskHandlers[i]->getTasks());
    Serial.println("Tasks inserted: " + String(i));
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