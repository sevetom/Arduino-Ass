#ifndef __SONAR_TASK__
#define __SONAR_TASK__

#include "Task.h"
#include "Sonar.h"

typedef enum {
  MIN,
  MAX
} SonarMode;

// time to wait before the car is considered to be in the washing machine
#define N2 2000
// time to wait before the car is considered to be out of the washing machine
#define N4 4000
#define MIN_DIST 0.2
#define MAX_DIST 0.8

/**
 * Task that handles the sonar sensor
*/
class SonarTask : public Task {
private:
  Sonar* sonar;
  using InterruptFunction = void (*)();
  InterruptFunction intFun;
  bool reading;
  // holds the current time since the car reached the treshold
  long tresholdTime;
  SonarMode mode;
public:
  /**
   * Initialize a sonar task
   * @param sonar The sonar sensor to use
   * @param intFun The function to call when the car reaches the treshold
   * @param mode The mode of the sonar sensor
  */
  SonarTask(Sonar* sonar, InterruptFunction intFun, SonarMode mode);
  void init(int period);
  void tick();
  /**
   * Sets the sonar in its reading state
  */
  void setReading(bool state);
};

#endif