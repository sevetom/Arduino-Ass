#ifndef __PROCEEDING_HANDLER__
#define __PROCEEDING_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "GateTask.h"
#include "SonarTask.h"

#define PROCEEDING_TASKS_COUNT 4
#define PROC_LED_PIN 13
#define PROC_GATE_PIN 5
#define PROC_TRIG_PIN 7
#define PROC_ECHO_PIN 8

class ProceedingHandler : public TaskHandler{
private:
  LcdTask* lcd;
  LedTask* led;
  GateTask* gate;
  SonarTask* sonar;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  int getTasksCount();
};

#endif