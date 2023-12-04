#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

/**
 * Class to handle a generic task
*/
class Task {
protected:
  long myPeriod;
  long timeElapsed;
  
public:
  /**
   * Initializes the task period
   * @param period The period of the task
  */
  virtual void init(long period){
    myPeriod = period;  
    timeElapsed = 0;
  }

  /**
   * The function to call to update the task
  */
  virtual void tick() = 0;

  /**
   * Checks if enough time has passed to update the task
   * @param basePeriod The base period of the scheduler
   * @return True if enough time has passed, false otherwise
  */
  bool updateAndCheckTime(long basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed -= myPeriod;
      return true;
    } else {
      return false; 
    }
  }

  /**
   * Resets the task
  */
  virtual void restart() {
    timeElapsed = 0;
  }
};

#endif

