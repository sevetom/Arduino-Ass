#include <Arduino.h>
#include <Components.h>

#define MIN_PERC 0
#define MAX_PERC 100
#define INVALID -1

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
    hw = new Components();
    currentModality = AUTOMATIC;
    currentAngle = 0;
    lastAngle = 0;
    hw->button->setInterrupt(changeModality, true);
    hw->servo->on();
    hw->lcd->printText("Angle: ", 0, 0);
    hw->lcd->printText("Modality: ", 0, 1);
}

void loop() {
    int value = INVALID;
    switch (currentModality) {
        case AUTOMATIC:
            value = serialReadInt();
            break;
        case MANUAL:
            Serial.println("AAAAAAAA");
            delay(100);
            value = hw->pot->detectChange() ? hw->pot->getValue() : INVALID;
            break;
    }
    if (value > 100) {
        changeModality();
    }
    if (value >= 0) {
        Serial.println("Value: " + String(value) + " Current angle: " + String(currentAngle));
        currentAngle = map(value, MIN_PERC, MAX_PERC, hw->servo->getMinAngle(), hw->servo->getMaxAngle());
        moveServo();
        printStatus();
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
    if (currentAngle != lastAngle) {
        Serial.println("Current angle: " + String(currentAngle) + " Last angle: " + String(lastAngle));
        int delta = 0;
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
        hw->servo->setPosition(90);
        delay(1000);
        lastAngle = currentAngle;
        Serial.println("Last angle: " + String(lastAngle));
    }
}

void printStatus() {
    Serial.println("Current angle: " + String(currentAngle) + " Modality: " + String(currentModality));
    hw->lcd->printInt(currentAngle, 7, 0);
    hw->lcd->printText((currentModality == AUTOMATIC) ? "Automatic" : "Manual", 10, 1);
}