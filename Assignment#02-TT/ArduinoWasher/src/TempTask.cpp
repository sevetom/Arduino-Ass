#include "TempTask.h"

TempTask::TempTask(TempSensor* tempSensor){
    this->tempSensor = tempSensor;
    this->temp = 0;
    this->isError = false;
}

void TempTask::init(int period){
    Task::init(period);
}

void TempTask::tick(){
    this->temp = this->tempSensor->getTemperature();
    Serial.println("Packet: Temperature: " + String(this->temp));
    if (this->temp > 100) { //! TO CHANGE
        this->isError = true;
        Serial.println("Packet: Error: " + String(this->isError));
        do {
            check();
        } while (this->isError);
    }
}

void TempTask::check() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == RESOLVE) {
      this->isError = false;
    }
  }
}
