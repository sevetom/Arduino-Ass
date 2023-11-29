#include "SonarTask.h"

SonarTask::SonarTask(Sonar* sonar, InterruptFunction intFun, SonarMode mode) {
  this->sonar = sonar;
  this->intFun = intFun;
  this->reading = false;
  this->minimumTime = 0;
  this->mode = mode;
}

void SonarTask::init(int period){
  Task::init(period);
}

void SonarTask::tick(){
  if (this->reading) {
    long time = this->mode == MAX ? N4 : N2;
    if(this->mode == MAX ? 
      this->sonar->getDistance() < MIN_DIST : 
      this->sonar->getDistance() > MAX_DIST) {
      if (this->minimumTime >= time) {
        this->setReading(false);
        this->minimumTime = 0;
        this->intFun();
      } else {
        this->minimumTime += this->myPeriod + this->timeElapsed;
      } 
    }
  }
}

void SonarTask::setReading(bool state) {
  this->reading = state;
}