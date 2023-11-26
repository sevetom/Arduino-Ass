#include "StateHandlerTask.h"

StateHandlerTask::StateHandlerTask(Scheduler* sched, TaskHandler** taskHandlers) {
  this->sched = sched;
  this->taskHandlers = taskHandlers;
  this->change = false;
  this->currentHandler = -1;
  this->handlerCount = 0;
  while (taskHandlers[this->handlerCount] != NULL) {
    this->handlerCount++;
  }
}

void StateHandlerTask::changeState() {
  this->change = true;
}

void StateHandlerTask::init(int period) {
  Task::init(period);
}

void StateHandlerTask::tick() {
  if (this->change) {
    this->changeTasks();
    this->change = false;
  }
}

void StateHandlerTask::changeTasks() {
  Serial.println("Changing tasks...");
  if (this->currentHandler != -1) {
    this->sched->removeTasks(taskHandlers[currentHandler]->getTasks());
    this->taskHandlers[currentHandler]->setChangeState(false);
  }
  this->currentHandler = currentHandler >= this->handlerCount ? 0 : currentHandler+1;
  this->taskHandlers[currentHandler]->setChangeState(true);
  insertTasks(this->taskHandlers[currentHandler]->getTasks());
  Serial.println("Tasks changed!");
}

void StateHandlerTask::insertTasks(Task** list) {
  int cur = 0;
  while(list[cur] != NULL) {
    this->sched->addTask(list[cur]);
    cur++;
  }
}