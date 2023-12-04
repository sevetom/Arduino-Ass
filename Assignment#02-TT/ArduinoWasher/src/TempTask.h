#ifndef __TEMP_TASK__
#define __TEMP_TASK__

#include "Task.h"
#include "TempSensor.h"
#include "LcdDisplay.h"
#include "LcdTask.h"

#define RESOLVE '1'
#define TEMP_THRESHOLD 20.0
#define N5 2*1000

class TempTask : public Task {
private:
  TempSensor* tempSensor;
  LcdDisplay* lcd;
  LcdTask* lcdTask;
  float temp;
  bool isError;
  long minimumTime;
public:
    TempTask(TempSensor* tempSensor, LcdDisplay* lcdDisplay, LcdTask* lcdTask);
    void init(int period);
    void tick();
    void setError();
    void checkResolution();
};

#endif