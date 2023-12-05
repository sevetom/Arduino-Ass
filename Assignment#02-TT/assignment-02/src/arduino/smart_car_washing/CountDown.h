#ifndef __COUNT_DOWN__
#define __COUNT_DOWN__

#include "Task.h"
#include <Arduino.h>

/**
 * Task that handles a timer
*/
class CountDown : public Task {
private:
  long waitTime;
  long currentTime;
  bool isRunning;
  using InterruptFun = void (*)(void);
  InterruptFun interruptFunction;
public:
  /**
   * Initialize a countdown timer task
   * @param time The time to count down from
   * @param f The function to call when the timer reaches 0
  */
  CountDown(long time, InterruptFun f);
  void init(int period);
  void tick();
  /**
   * Starts the timer
  */
  void start();
  /**
   * Stops the timer
  */
  void reset();
  /**
   * Returns the time passed since the timer started
  */
  long getTime();
  /**
   * Restarts the timer
  */
  void restart();
  /**
   * Resets the time passed since the timer started
  */
  void resetTime();
};

#endif