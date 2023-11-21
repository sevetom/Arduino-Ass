#include "SleepHandler.h"

void SleepHandler::initTasks(){
  this->pir = new Pir(PIR_PIN);
  this->pir->init();
  sleep = new SleepTask();
  sleep->init(150);
  tasksHandled[0] = sleep;
}

int SleepHandler::getInterruptPin() {
  return PIR_PIN;
}

void SleepHandler::afterInterrupt() {
  sleep_disable();
  delay(200);
  Serial.println("Sono sveglio, Danilooo!");
}