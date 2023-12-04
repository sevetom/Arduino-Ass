#include "TempTask.h"

TempTask::TempTask(TempSensor* tempSensor, LcdDisplay* lcdDisplay) {
    this->tempSensor = tempSensor;
    this->lcd = lcdDisplay;
    this->temp = 0;
    this->isError = false;
    this->minimumTime = 0;
}

void TempTask::init(int period){
    Task::init(period);
}

void TempTask::tick(){
  this->temp = this->tempSensor->getTemperature();
  Serial.println("Packet: Temperature: " + String(this->temp));
  if (this->temp > TEMP_THRESHOLD) {
    if (this->minimumTime >= N5) {
        this->setError();
      } else {
        this->minimumTime += this->myPeriod + this->timeElapsed;
      } 
  } else {
    this->minimumTime = 0;
  }
}

void TempTask::setError() {
  this->lcd->clear();
  this->lcd->printLong("Detected a Problem \n - Please Wait");
  this->isError = true;
  Serial.println("Packet: Error: " + String(this->isError));
  do {
      this->checkResolution();
  } while (this->isError);
  this->lcd->clear();
  this->lcd->printLong("Washing: ");
  this->minimumTime = 0;
}

void TempTask::checkResolution() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == RESOLVE) {
      this->isError = false;
    }
  }
}
