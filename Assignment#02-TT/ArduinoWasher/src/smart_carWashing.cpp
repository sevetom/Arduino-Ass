#include <Arduino.h>
#include <EnableInterrupt.h>
#include "Scheduler.h"
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

void changeTasks();
void insertTasks(Task** list);

Scheduler sched;
TaskHandler* taskHandlers[TASK_HANDLERS];
int currentHandler;

void setup() {
	Serial.begin(9600);
  sched.init(50);
  Serial.println("Inizio setup");
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
    taskHandlers[i]->initTasks();
  }
  currentHandler = 0;
  enableInterrupt(taskHandlers[currentHandler]->getInterruptPin(), changeTasks, CHANGE);
  insertTasks(taskHandlers[currentHandler]->getTasks());
  Serial.println("Setup completato");
}

void loop() {
	sched.schedule();
}

void changeTasks() {
  Serial.println("Cambio task");
  delay(200);
  taskHandlers[currentHandler]->afterInterrupt();
  Serial.println("Dopo afterInterrupt");
  sched.removeTasks(taskHandlers[currentHandler]->getTasks());
	disableInterrupt(taskHandlers[currentHandler]->getInterruptPin());
  currentHandler = currentHandler >= TASK_HANDLERS ? 0 : currentHandler+1;
  enableInterrupt(taskHandlers[currentHandler]->getInterruptPin(), changeTasks, CHANGE);
  insertTasks(taskHandlers[currentHandler]->getTasks());
}

void insertTasks(Task** list) {
  int cur = 0;
  while(list[cur] != NULL) {
    sched.addTask(list[cur]);
    cur++;
  }
}