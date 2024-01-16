#ifndef __COMPONENTS__
#define __COMPONENTS__

#include "Valve.h"
#include "Button.h"
#include "LcdDisplay.h"
#include "Potentiometer.h"

#define VALVE_PIN 9
#define BUTTON_PIN 2
#define POT_PIN A0

/**
 * Class that contains all the components of the washing machine
*/
class Components {
public:
    Valve* valve;
    Button* button;
    LcdDisplay* lcd;
    Potentiometer* pot;
public:
    /**
     * Constructor that initializes all the components
     */
    Components() {
        this->valve = new Valve(VALVE_PIN);
        this->button = new Button(BUTTON_PIN);
        this->lcd = new LcdDisplay();
        this->pot = new Potentiometer(POT_PIN, this->valve->getMinAngle(), this->valve->getMaxAngle());
    }
};

#endif