#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(long basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  this->nTasks = 0;
  this->startWindow = 1;
  this->endWindow = 1;
}

bool Scheduler::addTask(Task* task){
  if (this->nTasks < MAX_TASKS-1){
    this->taskList[nTasks] = task;
    this->nTasks++;
    return true;
  } else {
    return false; 
  }
}

void Scheduler::shiftTasks(int shift){
  this->startWindow = this->endWindow;
  this->endWindow += shift;
}

void Scheduler::resetWindow(){
  this->startWindow = 1;
  this->endWindow = 1;
}
  
void Scheduler::schedule(){   
  while (!timerFlag){}
  Timer1.setPeriod(this->basePeriod*1000l);
  timerFlag = false;
  if (this->taskList[0]->updateAndCheckTime(this->basePeriod)) {
    this->taskList[0]->tick();
  }
  for (int i = this->startWindow; i < this->endWindow; i++){
    if (this->taskList[i]->updateAndCheckTime(this->basePeriod)){
      this->taskList[i]->tick();
    }
  }
}

void Scheduler::printTasks(){
  for (int i = 0; i < this->nTasks; i++){
    Serial.println("Task: " + String(i));
  }
}