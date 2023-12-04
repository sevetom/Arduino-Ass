#ifndef __WELCOME_HANDLER__
#define __WELCOME_HANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "LcdTask.h"
#include "CountDown.h"

#define WELCOME_TASKS_COUNT 3
// time to wait for welcoming the car
#define N1 5000

/**
 * Task handler that handles the tasks when the car is first welcomed
*/
class WelcomeHandler : public TaskHandler {
private:
  LedTask* led; // 2
  LcdTask* lcd; // 3
  CountDown* timer; // 4
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif