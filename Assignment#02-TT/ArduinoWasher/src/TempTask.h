#ifndef __TEMP_TASK__
#define __TEMP_TASK__

#include "Task.h"
#include "TempSensor.h"

class TempTask : public Task {
private:
  TempSensor* tempSensor;
  float temp;
public:
    TempTask(TempSensor* tempSensor);
    void init(int period);
    void tick();
};

#endif