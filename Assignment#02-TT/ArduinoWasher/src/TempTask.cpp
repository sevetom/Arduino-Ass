#include "TempTask.h"

TempTask::TempTask(TempSensor* tempSensor, LcdTask* lcdTask) {
    this->tempSensor = tempSensor;
    this->lcd = lcdTask->getLcd();
    this->lcdTask = lcdTask;
    this->temp = 0;
    this->isError = false;
    this->tresholdTime = 0;
}

void TempTask::init(int period){
    Task::init(period);
}

void TempTask::tick(){
  /**
   * First sends the temperature to the serial monitor
  */
  this->temp = this->tempSensor->getTemperature();
  Serial.println("Packet: Temperature: " + String(this->temp));
  /**
   * If the temperature is too high for too long sets the error state
  */
  if (this->temp > TEMP_THRESHOLD || this->temp == 0) {
    if (this->tresholdTime >= N5) {
        this->setError();
      } else {
        this->tresholdTime += this->myPeriod + this->timeElapsed;
      } 
  } else {
    this->tresholdTime = 0;
  }
}

void TempTask::setError() {
  this->lcd->clear();
  this->lcd->printLong("Detected a Problem \n - Please Wait");
  this->isError = true;
  Serial.println("Packet: Error: " + String(this->isError));
  /**
   * Waits for the error to be resolved
  */
  do {
      this->checkResolution();
  } while (this->isError);
  this->lcdTask->restart();
  this->tresholdTime = 0;
}

void TempTask::checkResolution() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == RESOLVE) {
      this->isError = false;
    }
  }
}
