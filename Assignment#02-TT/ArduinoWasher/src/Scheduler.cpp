#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(unsigned long basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  this->nTasks = 0;
  this->startWindow = 1;
  this->endWindow = 1;
  this->lastLoopTime = 0;
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
  for (int i = 0; i < this->nTasks; i++){
    this->taskList[i]->restart();
  }
  this->startWindow = 1;
  this->endWindow = 1;
}
  
void Scheduler::schedule(){
  while (millis() - this->lastLoopTime <= this->basePeriod){}
  this->lastLoopTime = millis();
  timerFlag = false;
  if (this->taskList[0]->updateAndCheckTime(this->basePeriod)) {
    this->taskList[0]->tick();
  }
  for (int i = this->startWindow; i < this->endWindow; i++){
    if (this->taskList[i]->updateAndCheckTime(this->basePeriod)){
      Serial.println("Tasks: " + String(i));
      this->taskList[i]->tick();
      delay(1);
    }
  }
}