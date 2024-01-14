#include "servoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin){
  this->pin = pin;  
}

void ServoMotor::on(){
  this->motor.attach(pin);    
}

void ServoMotor::setPosition(int angle){
  this->motor.write(angle);              
}

void ServoMotor::off(){
  this->motor.detach();
}

int ServoMotor::getMinAngle(){
  return MIN_ANGLE;
}

int ServoMotor::getMaxAngle(){
  return MAX_ANGLE;
}
