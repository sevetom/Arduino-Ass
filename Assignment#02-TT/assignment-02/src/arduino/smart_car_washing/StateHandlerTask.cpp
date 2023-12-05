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
  if (this->currentHandler != -1) {
    this->taskHandlers[currentHandler]->setChangeState(false);
  }
  this->currentHandler++;
  if (this->currentHandler >= this->handlerCount) {
    Serial.println("Packet: Car Washed: 1");
    this->currentHandler = 0;
    this->sched->resetWindow();
  }
  this->taskHandlers[currentHandler]->setChangeState(true);
  this->sched->shiftTasks(this->taskHandlers[currentHandler]->getTasksCount());
}

