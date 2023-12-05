#ifndef __TEMP_TASK__
#define __TEMP_TASK__

#include "Task.h"
#include "TempSensor.h"
#include "LcdDisplay.h"
#include "LcdTask.h"

// if this symbol iis received than the temperature error is resolved
#define RESOLVE '1'
#define TEMP_THRESHOLD 50.0
// time to wait before the temperature is considered to be too high
#define N5 3*1000

class TempTask : public Task {
private:
  TempSensor* tempSensor;
  LcdDisplay* lcd;
  LcdTask* lcdTask;
  float temp;
  bool isError;
  long tresholdTime;
public:
  /**
   * Initialize a temperature task
   * @param tempSensor The temperature sensor to use
   * @param lcdTask The lcd task to use
  */
  TempTask(TempSensor* tempSensor, LcdTask* lcdTask);
  void init(int period);
  void tick();
  /**
   * Sets the entire system in a state of error
  */
  void setError();
  /**
   * Checks if the error has been resolved
  */
  void checkResolution();
};

#endif