#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include <Servo.h>

#define MIN_ANGLE 0
#define MAX_ANGLE 180

class ServoMotor {

public:
  ServoMotor(int pin);

  void on();
  void setPosition(int angle);
  void off();
  int getMinAngle();
  int getMaxAngle();
    
private:
  int pin; 
  Servo motor; 
};

#endif
