#ifndef __ENTERED_HANDLER__
#define __ENTERED_HANDLER__

#include "TaskHandler.h"
#include "LcdTask.h"
#include "LedTask.h"
#include "GateTask.h"
#include "Button.h"

#define ENT_TASKS_COUNT 3
#define ENT_LED_PIN 13
#define ENT_BUTTON_PIN 3
#define ENT_GATE_PIN 5

class EnteredHandler : public TaskHandler {
private:
  LcdTask* lcd;
  LedTask* led;
  GateTask* gate;
  Button* button;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  int getTasksCount();
};

#endif