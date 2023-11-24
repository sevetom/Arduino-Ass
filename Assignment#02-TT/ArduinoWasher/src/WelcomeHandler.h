#ifndef __WELCOME_HANDLER__
#define __WELCOME_HANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "LcdTask.h"
#include "CountDown.h"

#define LED_PIN 5
#define N1 5

class WelcomeHandler : public TaskHandler {
private:
  LedTask* led;
  LcdTask* lcd;
  CountDown* timer;
public:
  void initTasks(ChangeFun f);
  void setChangeState(bool state);
  void afterChangeState();
};

#endif