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

/**
 * Main file of the project
 * @author tommaso.ceredi@studio.unibo.it
 * @author tommaso.severi2@studio.unibo.it
*/

#define TASK_HANDLERS 7

/**
 * Enum that represents the states of the state machine
*/
typedef enum {
  SLEEPING,
  WELCOME,
  PROCEEDING,
  ENTERED,
  WASHING,
  EXITING,
  LEAVED
} taskHandlerState;

/**
 * Function that inserts the tasks of a task handler in the scheduler
*/
void insertTasks(Task** list, int lenght);

Scheduler* sched;
WashingComponents* hw;
TaskHandler* taskHandlers[TASK_HANDLERS];
StateHandlerTask* stateHandlerTask;

void setup() {
	Serial.begin(9600);
  hw = new WashingComponents();
  sched = new Scheduler();
  sched->init(50);
  // inits the state handler task
  stateHandlerTask = new StateHandlerTask(sched, taskHandlers, TASK_HANDLERS);
  stateHandlerTask->init(150);
  sched->addTask(stateHandlerTask);
  // creates the task handlers
  taskHandlers[SLEEPING] = new SleepHandler();
  taskHandlers[WELCOME] = new WelcomeHandler();
  taskHandlers[PROCEEDING] = new ProceedingHandler();
  taskHandlers[ENTERED] = new EnteredHandler();
  taskHandlers[WASHING] = new WashingHandler();
  taskHandlers[EXITING] = new ExitingHandler();
  taskHandlers[LEAVED] = new LeavedHandler();
  // inits the task handlers
  for (int i = 0; i < TASK_HANDLERS; i++){
    taskHandlers[i]->setHandler([](){ stateHandlerTask->changeState(); }, hw);
    taskHandlers[i]->initTasks();
    insertTasks(taskHandlers[i]->getTasks(), taskHandlers[i]->getTasksCount());
    delay(100);
  }
  // starts the first task hanlder
  stateHandlerTask->changeTasks();
}

void loop() {
	sched->schedule();
}

void insertTasks(Task** list, int lenght) {
  for (int i = 0; i < lenght; i++) {
    sched->addTask(list[i]);
  }
}