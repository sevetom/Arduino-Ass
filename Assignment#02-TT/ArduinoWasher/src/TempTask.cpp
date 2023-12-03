#include "TempTask.h"

TempTask::TempTask(TempSensor* tempSensor){
    this->tempSensor = tempSensor;
    this->temp = 0;
}

void TempTask::init(int period){
    Task::init(period);
}

void TempTask::tick(){
    this->temp = this->tempSensor->getTemperature();
    Serial.println("Packet: Temperature: " + String(this->temp));
}

