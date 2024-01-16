#include "Valve.h"
#include "Arduino.h"

Valve::Valve(int pin){
  this->pin = pin;  
}

void Valve::on(){
  this->motor.attach(pin);    
}

void Valve::setPosition(int angle){
  this->motor.write(angle);              
}

void Valve::off(){
  this->motor.detach();
}

int Valve::getMinAngle(){
  return MIN_ANGLE;
}

int Valve::getMaxAngle(){
  return MAX_ANGLE;
}
