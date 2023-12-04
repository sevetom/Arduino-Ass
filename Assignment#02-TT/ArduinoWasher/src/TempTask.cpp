#include "TempTask.h"

TempTask::TempTask(TempSensor* tempSensor, LcdDisplay* lcdDisplay, LcdTask* lcdTask) {
    this->tempSensor = tempSensor;
    this->lcd = lcdDisplay;
    this->lcdTask = lcdTask;
    this->temp = 0;
    this->isError = false;
    this->minimumTime = 0;
}

void TempTask::init(int period){
    Task::init(period);
}

void TempTask::tick(){
  this->temp = this->tempSensor->getTemperature();
  Serial.println("Packet: Temperature: " + String(this->temp) + " minimumTime: " + String(this->minimumTime));
  if (this->temp > TEMP_THRESHOLD || this->temp == 0) {
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
  this->lcdTask->restart();
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
