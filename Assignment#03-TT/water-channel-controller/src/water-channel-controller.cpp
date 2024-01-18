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
volatile long timer;

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(4);
    hw = new Components();
    modality = AUTOMATIC;
    currentAngle = 0;
    lastAngle = 0;
    //hw->button->setInterrupt(changeModality, true);
    hw->lcd->printText("Angle: ", 0, 0);
    hw->lcd->printText("Mod: ", 0, 1);
    hw->valve->on();
    timer = 0;
}

void loop() {
    // value starts as not needing an update
    int value = INVALID;
    // if the system is in manual mode then reads for a change in the potentiometer
    if (modality == MANUAL) {
        value = hw->pot->detectChange() ? hw->pot->getValue() : INVALID;
        if (value == AUTOMATIC || value == MANUAL) {
            value = INVALID;
        }
    }
    /** if the values is still invalid then there could be two cases:
     *  1. the system is in automatic mode so we need the water level
     *  2. the system is in manual mode and the potentiometer has not changed
     *     but we still need to check for a modality change made from the frontend */
    if (value == INVALID) {
        value = serialReadInt();
    }
    // it's possible that it's needed to switch to manual mode
    if (value == AUTOMATIC || value == MANUAL) {
        Serial.println("AR set modality: " + String(value));
        modality = value;
        printStatus();
        timer = 1;
    }
    // once everything is done we can update the angle if needed
    if (value >= MIN_PERC && value <= MAX_PERC) {
        currentAngle = map(value, MIN_PERC, MAX_PERC, hw->valve->getMinAngle(), hw->valve->getMaxAngle());
        if (currentAngle != lastAngle) {
            moveValve();
            printStatus();
        }
    }
    if (timer > 0) {
        timer ++;
        if (timer > 50000){
            timer = 0;
            Serial.println("PRONTO?!?!?!?");
            delay(2000);
            Serial.println("3");
            delay(1000);
            Serial.println("2");
            delay(1000);
            Serial.println("1");
            delay(1000);
            Serial.println("Premi");
            modality = AUTOMATIC;
            Serial.println("Modality: " + String(modality));
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