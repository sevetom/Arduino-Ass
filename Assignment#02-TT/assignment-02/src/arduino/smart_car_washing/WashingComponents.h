#ifndef __COMPONENTS__
#define __COMPONENTS__

#include "Led.h"
#include "Pir.h"
#include "Sonar.h"
#include "Gate.h"
#include "LcdDisplay.h"
#include "Button.h"
#include "TempSensor.h"

#define GREEN_LED1_PIN 7
#define RED_LED_PIN 4
#define GREEN_LED3_PIN 6
#define PIR_PIN 2
#define SONAR_TRIG_PIN 10
#define SONAR_ECHO_PIN 9
#define SERVO_PIN 11
#define BUTTON_PIN 3
#define TEMP_SENSOR_PIN A3

/**
 * Class that contains all the components of the washing machine
*/
class WashingComponents {
public:
  Led* green1;
  Led* red2;
  Led* green3;
  Pir* pir;
  Sonar* sonar;
  Gate* gate;
  LcdDisplay* lcd;
  Button* button;
  TempSensor* tempSensor;
public:
  /**
   * Constructor that initializes all the components
  */
  WashingComponents() {
    this->green1 = new Led(GREEN_LED1_PIN);
    this->red2 = new Led(RED_LED_PIN);
    this->green3 = new Led(GREEN_LED3_PIN);
    this->pir = new Pir(PIR_PIN);
    this->sonar = new Sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
    this->gate = new Gate(SERVO_PIN);
    this->lcd = new LcdDisplay();
    this->button = new Button(BUTTON_PIN);
    this->tempSensor = new TempSensor(TEMP_SENSOR_PIN);
  }
};

#endif