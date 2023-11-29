#ifndef __SONAR_TASK__
#define __SONAR_TASK__

#include "Task.h"
#include "Sonar.h"

typedef enum {
  MIN,
  MAX
} SonarMode;

#define N2 2000
#define N4 4000
#define MIN_DIST 0.2

class SonarTask : public Task {
private:
  Sonar* sonar;
  using InterruptFunction = void (*)();
  InterruptFunction intFun;
  bool reading;
  long minimumTime;
  SonarMode mode;
public:
  SonarTask(int trigPin, int echoPin, InterruptFunction intFun, SonarMode mode);
  void init(int period);
  void tick();
  void setReading(bool state);
};

#endif