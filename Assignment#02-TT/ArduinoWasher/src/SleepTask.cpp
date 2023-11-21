#include "SleepTask.h"

SleepTask::SleepTask() { }

void SleepTask::init(int period) {
  Task::init(period);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void SleepTask::tick() {
  Serial.println("Vado a letto...");
  delay(200);
  sleep_enable();
  sleep_mode();
}
