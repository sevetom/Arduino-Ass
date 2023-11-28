#include "StateHandlerTask.h"

StateHandlerTask::StateHandlerTask(Scheduler* sched, TaskHandler** taskHandlers, int handlerCount) {
  this->sched = sched;
  this->taskHandlers = taskHandlers;
  this->change = false;
  this->currentHandler = -1;
  this->handlerCount = handlerCount;
}

void StateHandlerTask::changeState() {
  this->change = true;
}

void StateHandlerTask::init(int period) {
  Task::init(period);
}

void StateHandlerTask::tick() {
  if (this->change == true) {
    this->change = false;
    this->changeTasks();
  }
}

void StateHandlerTask::changeTasks() {
  Serial.println("Changing tasks...");
  if (this->currentHandler != -1) {
    this->taskHandlers[currentHandler]->setChangeState(false);
  }
  this->currentHandler = this->currentHandler >= this->handlerCount ? 0 : this->currentHandler+1;
  this->taskHandlers[currentHandler]->setChangeState(true);
  this->sched->shiftTasks(this->taskHandlers[currentHandler]->getTasksCount());
  Serial.println("Tasks changed!");
}

