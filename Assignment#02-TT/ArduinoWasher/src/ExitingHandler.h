#ifndef __EXITING_HANDLER__
#define __EXITING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "SonarTask.h"

#define EXT_TASKS_COUNT 4
#define EXT_GREEN_LED_PIN 12
#define EXT_RED_LED_PIN 13
#define EXT_SONAR_TRIG_PIN 7
#define EXT_SONAR_ECHO_PIN 8

class ExitingHandler : public TaskHandler {
private:
  LcdTask* lcd;
  LedTask* greenLed;
  LedTask* redLed;
  SonarTask* sonar;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  int getTasksCount();
};

#endif