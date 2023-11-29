#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "Task.h"
#include "LcdDisplay.h"
#include "CountDown.h"

typedef enum {
  PRINT,
  LOADING_BAR
} LcdMode;

class LcdTask : public Task {
private:
  LcdDisplay* lcd;
  const char* message;
  CountDown* timer;
  LcdMode mode;
  int percentage;
public:
  LcdTask(const char* message);
  LcdTask(const char* message, CountDown* timer);
  void init(int period);
  void tick();
};

#endif