#ifndef __COMPONENTS__
#define __COMPONENTS__

#include "Gate.h"
#include "Button.h"
#include "LcdDisplay.h"
#include "Potentiometer.h"

#define SERVO_PIN 11
#define BUTTON_PIN 2
#define POT_PIN A0

/**
 * Class that contains all the components of the washing machine
*/
class Components {
public:
    Gate* gate;
    Button* button;
    LcdDisplay* lcd;
    Potentiometer* pot;
public:
    /**
     * Constructor that initializes all the components
     */
    Components() {
        this->gate = new Gate(SERVO_PIN);
        this->button = new Button(BUTTON_PIN);
        this->lcd = new LcdDisplay();
        this->pot = new Potentiometer(POT_PIN, this->gate->getMinAngle(), this->gate->getMaxAngle());
    }
};

#endif