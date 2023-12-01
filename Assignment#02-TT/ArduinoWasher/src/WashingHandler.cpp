#include "WashingHandler.h"

void WashingHandler::initTasks(){
    led = new LedTask(this->hw->red2, BLINK);
    led->init(500);
    timer = new CountDown(WASH_TIME, this->changeFun);
    timer->init(150);
    lcd = new LcdTask(this->hw->lcd, "Washing:", timer);
    lcd->init(150);
    this->tasksHandled[0] = led;
    this->tasksHandled[1] = lcd;
    this->tasksHandled[2] = timer;
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