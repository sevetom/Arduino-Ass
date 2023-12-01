#ifndef __TASK__
#define __TASK__

#include <Arduino.h>
class Task {
protected:
  long myPeriod;
  long timeElapsed;
  
public:
  virtual void init(long period){
    myPeriod = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(long basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed -= myPeriod;
      return true;
    } else {
      return false; 
    }
  }

  virtual void restart() {
    timeElapsed = 0;
  }
};

#endif

