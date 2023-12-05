#include "SleepTask.h"

void SleepTask::init(int period) {
  Task::init(period);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void SleepTask::tick() {
  /**
   * Every time the task is called, the Arduino goes to sleep
  */
  Serial.println("Going to sleep...");
  Serial.flush();
  sleep_enable();
  sleep_mode();

  sleep_disable();
}