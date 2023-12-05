#ifndef __LCD_TASK__
#define __LCD_TASK__

#include "Task.h"
#include "LcdDisplay.h"
#include "CountDown.h"

typedef enum {
  PRINT,
  LOADING_BAR
} LcdMode;

/**
 * Task that handles the LCD display
*/
class LcdTask : public Task {
private:
  LcdDisplay* lcd;
  const char* message;
  CountDown* timer;
  LcdMode mode;
  int percentage;
  // used to check if the message has already been printed
  bool printStatus;
public:
  /**
   * Initialize a LCD task
   * @param lcd The LCD display to use
   * @param message The message to print on the LCD display
  */
  LcdTask(LcdDisplay* lcd, const char* message);
  /**
   * Initialize a LCD task that prints a loading bar
   * @param lcd The LCD display to use
   * @param message The message to print on the LCD display
   * @param timer The timer to use
  */
  LcdTask(LcdDisplay* lcd, const char* message, CountDown* timer);
  void init(int period);
  void tick();
  void restart();
  /**
   * Returns the LCD display
   * @return The LCD display
  */
  LcdDisplay* getLcd();
};

#endif