#ifndef __COMPONENTS__
#define __COMPONENTS__

#include "Led.h"
#include "Sonar.h"

#define GREEN_LED 2
#define RED_LED 4
#define SONAR_TRIG 12
#define SONAR_ECHO 14

/**
 * Class that contains all the components of the washing machine
*/
class Components {
public:
    Led* greenLed;
    Led* redLed;
    Sonar* sonar;
public:
    /**
     * Constructor that initializes all the components
     */
    Components() {
        this->greenLed = new Led(GREEN_LED);
        this->redLed = new Led(RED_LED);
        this->sonar = new Sonar(SONAR_TRIG, SONAR_ECHO);
    }
};

#endif