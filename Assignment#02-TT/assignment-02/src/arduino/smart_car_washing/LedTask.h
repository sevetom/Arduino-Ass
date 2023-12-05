#ifndef __LED_TASK__
#define __LED_TASK__

#include "Task.h"
#include "Led.h"

typedef enum {
  ON,
  OFF,
  BLINK
} ledMode;

/**
 * Task that handles a LED
*/
class LedTask : public Task {
private:
  Led* led;
  ledMode mode;
public:
  /**
   * Initialize a LED task
   * @param led The LED to use
   * @param mode The mode of the LED
  */
  LedTask(Led* led, ledMode mode);
  void init(int period);
  void tick();
};

#endif