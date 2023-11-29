#include "WashingHandler.h"

void WashingHandler::initTasks(ChangeFun f){
    led = new LedTask(WASH_LED_PIN, ON);
    led->init(150);
    timer = new CountDown(WASH_TIME, f);
    timer->init(150);
    lcd = new LcdTask("Washing:", timer);
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