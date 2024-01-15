#include <Arduino.h>
#include <Components.h>

#define MIN_PERC 0
#define MAX_PERC 100
#define INVALID -1
#define MODALITY_CHANGE 101

/**
 * @brief The modality of the system
*/
typedef enum {
    AUTOMATIC,
    MANUAL
} modality;

/**
 * @brief Change the modality of the system
*/
void changeModality();

/**
 * @brief Read the serial port and return the value if it is valid
 * @return The value read from the serial port or -1 if it is not valid
*/
int serialReadInt();

/**
 * @brief Move the servo to the current angle
*/
void moveServo();

/**
 * @brief Print the status of the system
*/
void printStatus();

volatile modality currentModality;
volatile int currentAngle;
volatile int lastAngle;
Components* hw;

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(4);
    Components* hw = new Components();
    currentModality = AUTOMATIC;
    currentAngle = 0;
    lastAngle = 0;
    hw->button->setInterrupt(changeModality, true);
}

void loop() {
    // value starts as not needing an update
    int value = INVALID;
    // if the system is in manual mode then reads for a change in the potentiometer
    if (currentModality == MANUAL) {
        value = hw->pot->detectChange() ? hw->pot->getValue() : INVALID;
    }
    /** if the values is still invalid then there could be two cases:
     *  1. the system is in automatic mode so we need the water level
     *  2. the system is in manual mode and the potentiometer has not changed
     *     but we still need to check for a manual change made from the frontend */
    if (value == INVALID) {
        value = serialReadInt();
    }
    // it's possible that it's needed to switch to manual mode
    if (value == MODALITY_CHANGE) {
        currentModality = MANUAL;
    }
    // once everything is done we can update the angle if needed
    if (value >= MIN_PERC && value <= MAX_PERC) {
        currentAngle = map(value, MIN_PERC, MAX_PERC, hw->servo->getMinAngle(), hw->servo->getMaxAngle());
        if (currentAngle != lastAngle) {
            // moveServo();
            // printStatus();
        }
    }
}

void changeModality() {
    if (hw->button->avoidBouncing()) {
        currentModality = (currentModality == AUTOMATIC) ? MANUAL : AUTOMATIC;
        Serial.println("Modality: " + String(currentModality));
    }
}

int serialReadInt() {
    if (Serial.available()) {
        int data = (int)Serial.parseInt();
        Serial.println("Data: " + String(data));
        return data;
    }
    return INVALID;
}

void moveServo() {
    Serial.println("Current angle: " + String(currentAngle) + " Last angle: " + String(lastAngle));
    int delta = 0;
    hw->servo->on();
    if (currentAngle > lastAngle) {
        delta = currentAngle - lastAngle;
        hw->servo->setPosition(80);
        delay(1000);
    } else {
        delta = lastAngle - currentAngle;
        hw->servo->setPosition(100);
        delay(1000);
    }
    Serial.println("Delta: " + String(delta));
    delay(delta);
    hw->servo->off();
    lastAngle = currentAngle;
    Serial.println("Last angle: " + String(lastAngle));
}

void printStatus() {
    hw->lcd->printInt(currentAngle, 0, 0);
    hw->lcd->printText((currentModality == AUTOMATIC) ? "Automatic" : "Manual", 0, 1);
}