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
    Serial.println("Task added " + String(this->nTasks));
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
  Serial.println("nTasks: " + String(this->nTasks));
  for (int i = 0; i < this->nTasks; i++){
    Serial.println("Restart task " + String(i));
    delay(10);
    this->taskList[i]->restart();
  }
  this->startWindow = 1;
  this->endWindow = 1;
}
  
void Scheduler::schedule(){   
  while (!timerFlag){}
  Timer1.setPeriod(this->basePeriod*1000l);
  timerFlag = false;
  if (this->taskList[0]->updateAndCheckTime(this->basePeriod)) {
    Serial.println("Tasks: 0");
    this->taskList[0]->tick();
    delay(1);
  }
  for (int i = this->startWindow; i < this->endWindow; i++){
    if (this->taskList[i]->updateAndCheckTime(this->basePeriod)){
      Serial.println("Tasks: " + String(i));
      this->taskList[i]->tick();
      delay(1);
    }
  }
}