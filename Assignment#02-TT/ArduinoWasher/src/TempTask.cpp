#include "TempTask.h"

TempTask::TempTask(TempSensor* tempSensor){
    this->tempSensor = tempSensor;
}

void TempTask::init(int period){
    Task::init(period);
}

void TempTask::tick(){
    this->temp = this->tempSensor->getTemperature();
    Serial.println("Temp: " + String(this->temp));
}

