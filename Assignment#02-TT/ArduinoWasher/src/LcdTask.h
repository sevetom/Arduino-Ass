#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "Task.h"
#include "LcdDisplay.h"
#include "CountDown.h"

#define FULL_BAR 16

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
  bool printStatus;
public:
  LcdTask(LcdDisplay* lcd, const char* message);
  LcdTask(LcdDisplay* lcd, const char* message, CountDown* timer);
  void init(int period);
  void tick();
  void restart();
};

#endif