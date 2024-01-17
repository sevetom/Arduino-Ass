#include <Arduino.h>
#include <Components.h>

/**
* @author tommaso.ceredi@studio.unibo.it
* @author tommaso.severi2@studio.unibo.it
*/

#define MIN_PERC 0
#define MAX_PERC 100
#define INVALID -1
#define MODALITY_CHANGE 101

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
volatile bool isManual;
Components* hw;
volatile long timer;

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(4);
    hw = new Components();
    isManual = false;
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
    if (isManual) {
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
        isManual = !isManual;
        Serial.println("Manual mode: " + String(isManual));
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
            isManual = !isManual;
            Serial.println("Modality: " + String(isManual));
            printStatus();
        }
    }
}

void changeModality() {
    //noInterrupts();
    if (hw->button->avoidBouncing()) {
        isManual = !isManual;
        Serial.println("Manual: " + String(isManual));
        delay(100);
        printStatus();
    }
    //interrupts();
}

int serialReadInt() {
    if (Serial.available()) {
        int data = (int)Serial.parseInt();
        data--;
        Serial.println("Data: " + String(data));
        return data;
    }
    return INVALID;
}

void moveValve() {
    Serial.println("Current angle: " + String(currentAngle) + " Last angle: " + String(lastAngle));
    int delta = 0;
    if (currentAngle > lastAngle) {
        delta = currentAngle - lastAngle;
        hw->valve->setPosition(40);
    } else {
        delta = lastAngle - currentAngle;
        hw->valve->setPosition(140);
    }
    Serial.println("Delta: " + String(delta));
    delay(delta*10);
    hw->valve->setPosition(90);
    lastAngle = currentAngle;
    Serial.println("Last angle: " + String(lastAngle));
}

void printStatus() {
    Serial.println("Current angle: " + String(currentAngle) + " Modality: " + String(isManual));
    hw->lcd->clear();
    hw->lcd->printText("Angle: ", 0, 0);
    hw->lcd->printText("Mod: ", 0, 1);
    hw->lcd->printInt(currentAngle, 7, 0);
    hw->lcd->printText(isManual ? "Manual" : "Auto", 5, 1);
}