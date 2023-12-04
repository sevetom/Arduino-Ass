#include "SonarTask.h"

SonarTask::SonarTask(Sonar* sonar, InterruptFunction intFun, SonarMode mode) {
  this->sonar = sonar;
  this->intFun = intFun;
  this->reading = false;
  this->tresholdTime = 0;
  this->mode = mode;
}

void SonarTask::init(int period){
  Task::init(period);
}

void SonarTask::tick(){
  /**
   * If the sonar is reading checks if the car
   * reached the treshold
  */
  if (this->reading) {
    long time = this->mode == MAX ? N4 : N2;
    float distance = this->sonar->getDistance();
    if(this->mode == MAX ? 
        distance > MAX_DIST : 
        distance < MIN_DIST) {
      /**
       * If the car reached the treshold calls the interrupt function
       * otherwise updates the time since the car reached the treshold
      */
      if (this->tresholdTime >= time) {
        this->setReading(false);
        this->tresholdTime = 0;
        this->intFun();
      } else {
        this->tresholdTime += this->myPeriod + this->timeElapsed;
      }
    } else {
      /**
       * resets the time if the car has not reached the treshold
       * or if the car has moved away from the treshold
      */
      this->tresholdTime = 0;
    }
  }
}

void SonarTask::setReading(bool state) {
  this->reading = state;
}