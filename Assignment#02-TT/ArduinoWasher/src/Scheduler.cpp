#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(int basePeriod){
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
  Serial.println("Start: " + String(this->startWindow) + " - End: " + String(this->endWindow) + " - Shift: " + String(shift));
}
  
void Scheduler::schedule(){   
  while (!timerFlag){}
  timerFlag = false;
  if (this->taskList[0]->updateAndCheckTime(basePeriod)) {
    Serial.println("Eseguo task: 0");
    this->taskList[0]->tick();
  }
  Serial.println("Entro nel for: " + String(this->startWindow) + " - " + String(this->endWindow));
  for (int i = this->startWindow; i < this->endWindow; i++){
    Serial.println("Controllo task: " + String(i));
    if (this->taskList[i]->updateAndCheckTime(basePeriod)){
      Serial.println("Eseguo task: " + String(i));
      this->taskList[i]->tick();
    }
  }
}
