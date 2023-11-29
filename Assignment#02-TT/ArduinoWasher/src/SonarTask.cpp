#include "SonarTask.h"

SonarTask::SonarTask(int trigPin, int echoPin, InterruptFunction intFun, SonarMode mode) {
  this->sonar = new Sonar(trigPin, echoPin);
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