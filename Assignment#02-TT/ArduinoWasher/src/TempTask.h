#ifndef __TEMP_TASK__
#define __TEMP_TASK__

#include "Task.h"
#include "TempSensor.h"

#define RESOLVE '1'
#define TEMP_THRESHOLD 51.0

class TempTask : public Task {
private:
  TempSensor* tempSensor;
  float temp;
  bool isError;
public:
    TempTask(TempSensor* tempSensor);
    void init(int period);
    void tick();
    void check();
};

#endif