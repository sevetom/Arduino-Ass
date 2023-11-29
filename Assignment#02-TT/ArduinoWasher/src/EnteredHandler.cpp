#include "EnteredHandler.h"

void EnteredHandler::initTasks(){
    lcd = new LcdTask(this->hw->lcd, "Ready to wash");
    lcd->init(150);
    led = new LedTask(this->hw->red2, ON);
    led->init(150);
    gate = new GateTask(this->hw->gate, CLOSE);
    gate->init(150);
    this->tasksHandled[0] = lcd;
    this->tasksHandled[1] = led;
    this->tasksHandled[2] = gate;
}

void EnteredHandler::setChangeState(bool state){
    this->hw->button->setInterrupt(this->changeFun, state);
}

int EnteredHandler::getTasksCount(){
    return ENT_TASKS_COUNT;
}