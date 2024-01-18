#include <Arduino.h>
#include <Components.h>

/**
* @author tommaso.ceredi@studio.unibo.it
* @author tommaso.severi2@studio.unibo.it
*/

#define MIN_PERC 0
#define MAX_PERC 100
#define INVALID -1
#define MANUAL 101
#define AUTOMATIC 102

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
 * @brief Move the valve to the current angle
*/
void moveValve();

/**
 * @brief Print the status of the system
*/
void printStatus();

volatile int currentAngle;
volatile int lastAngle;
volatile int modality;
Components* hw;

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(4);
    hw = new Components();
    modality = AUTOMATIC;
    currentAngle = 0;
    lastAngle = 0;
    hw->button->setInterrupt(changeModality, true);
    hw->lcd->printText("Angle: ", 0, 0);
    hw->lcd->printText("Mod: ", 0, 1);
    hw->valve->on();
}

void loop() {
    // value starts as not needing an update
    int value = INVALID;
    // reads the serial value in any case
    int serialValue = serialReadInt();
    // checks for a modality change
    if (serialValue == AUTOMATIC || serialValue == MANUAL) {
        noInterrupts();
        modality = serialValue;
        interrupts();
    } else {
        currentAngle = INVALID;
        if (modality == MANUAL) {
            currentAngle = hw->pot->detectChange() ? hw->pot->getValue() : INVALID;
        }
        // if the modality is automatic or the potentiometer has not changed
        // the serial value is used to update the angle
        if (currentAngle == INVALID) {
            if (serialValue >= MIN_PERC && serialValue <= MAX_PERC) {
                // needs to be mapped since it's a percentage
                currentAngle = map(serialValue, MIN_PERC, MAX_PERC, hw->valve->getMinAngle(), hw->valve->getMaxAngle());
            }
        }
        // only if a new angle is sampled and it's different from the last one it is updated
        if (currentAngle != INVALID && currentAngle != lastAngle) {
            moveValve();
            printStatus();
        }
    }
}

void changeModality() {
    if (hw->button->avoidBouncing()) {
        modality = modality == MANUAL ? AUTOMATIC : MANUAL;
        // Needed to comunicate the change to the service
        Serial.println("Manual: " + String(MANUAL));
        printStatus();
    }
}

int serialReadInt() {
    if (Serial.available()) {
        int data = (int)Serial.parseInt();
        /**
         * Every value needs to be decreased since 0 was
         * causing problems when communicated through the
         * serial line
        */
        data--;
        Serial.println("Data: " + String(data));
        return data;
    }
    return INVALID;
}

/**
 * This is an alternative versione made to work with a
 * particolar servo that only moves in two directions
 * with the value being the speed and stopping when
 * the value is 90
*/
void moveValve() {
    int delta = 0;
    if (currentAngle > lastAngle) {
        delta = currentAngle - lastAngle;
        hw->valve->setPosition(40);
    } else {
        delta = lastAngle - currentAngle;
        hw->valve->setPosition(140);
    }
    delay(delta*10);
    hw->valve->setPosition(90);
    lastAngle = currentAngle;
}

/**
 * This is the original versione made to work with a
 * normal servo that moves in all directions
*/
/*
void moveValve() {
    pMotor->on();
    for (int i = lastAngle; i != currentAngle; i += (currentAngle > lastAngle ? 1 : -1)) {
        pMotor->setPosition(pos);         
        delay(2);            
        pos += delta;
    }
    pMotor->off();
    lastAngle = currentAngle;
*/

void printStatus() {
    Serial.println("Angle: " + String(currentAngle) + " Modality: " + String(modality));
    hw->lcd->clear();
    hw->lcd->printText("Angle: ", 0, 0);
    hw->lcd->printText("Mod: ", 0, 1);
    hw->lcd->printInt(currentAngle, 7, 0);
    hw->lcd->printText(modality == MANUAL ? "Manual" : "Auto", 5, 1);
}