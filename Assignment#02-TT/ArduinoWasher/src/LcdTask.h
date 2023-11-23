#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "Task.h"
#include "LcdDisplay.h"

class LcdTask : public Task {
private:
  LcdDisplay* lcd;
public:
  LcdTask();
  void init(int period);
  void tick();
};

#endif