#include "WashingHandler.h"

void WashingHandler::initTasks(){
    this->led = new LedTask(this->hw->red2, BLINK);
    this->led->init(500);
    this->timer = new CountDown(WASH_TIME, this->changeFun);
    this->timer->init(150);
    this->lcd = new LcdTask(this->hw->lcd, "Washing:", timer);
    this->lcd->init(150);
    this->tempSensor = new TempTask(this->hw->tempSensor, this->lcd);
    this->tempSensor->init(150);
    this->tasksHandled[0] = led;
    this->tasksHandled[1] = lcd;
    this->tasksHandled[2] = timer;
    this->tasksHandled[3] = tempSensor;
}

void WashingHandler::setChangeState(bool state){
  if (state) {
    this->timer->start();
  } else {
    this->timer->reset();
  }
}

int WashingHandler::getTasksCount(){
    return WASH_TASKS_COUNT;
}