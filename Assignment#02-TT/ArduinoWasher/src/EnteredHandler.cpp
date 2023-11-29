#include "EnteredHandler.h"

void EnteredHandler::initTasks(ChangeFun f){
    TaskHandler::changeFun = f;
    lcd = new LcdTask("Ready to wash");
    lcd->init(150);
    led = new LedTask(ENT_LED_PIN, ON);
    led->init(150);
    gate = new GateTask(ENT_GATE_PIN, CLOSE);
    gate->init(150);
    button = new Button(ENT_BUTTON_PIN);
    this->tasksHandled[0] = lcd;
    this->tasksHandled[1] = led;
    this->tasksHandled[2] = gate;
}

void EnteredHandler::setChangeState(bool state){
    this->button->setInterrupt(TaskHandler::changeFun, state);
}

int EnteredHandler::getTasksCount(){
    return ENT_TASKS_COUNT;
}