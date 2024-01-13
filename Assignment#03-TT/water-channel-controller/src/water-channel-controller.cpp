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
/**
 * @brief Print the status of the system
*/
void printStatus();

volatile modality currentModality;
volatile char currentAngle;
Components* hw;

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(4);
    Components* hw = new Components();
    currentModality = AUTOMATIC;
    currentAngle = 0;
    hw->button->setInterrupt(changeModality, true);
    hw->lcd->printText("Modality: ", 0, 1);
    hw->lcd->printText("Angle: ", 0, 0);
}

void loop() {
    int value = INVALID;
    //noInterrupts();
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
    //interrupts();
    if (value >= 0) {
        Serial.println("Value: " + String(value));
        delay(100);
        currentAngle = map(value, MIN_PERC, MAX_PERC, hw->gate->getMinAngle(), hw->gate->getMaxAngle());
        Serial.print("Angle: ");
        Serial.println(currentAngle);
        delay(100);
        //hw->gate->setAngle(currentAngle);
        //printStatus();
        delay(100);
    }
}

void changeModality() {
    if (hw->button->avoidBouncing()) {
        currentModality = (currentModality == AUTOMATIC) ? MANUAL : AUTOMATIC;
        Serial.println("Modality: " + String(currentModality));
    }
}

int serialReadInt() {
    Serial.println("Serial read int");
    if (Serial.available()) {
        int data = Serial.parseInt();
        Serial.println("Data: " + String(data));
        while (Serial.available()) {
            Serial.read();
        }
        return data;
    }
    return INVALID;
}

void printStatus() {
    hw->lcd->printText(String(currentAngle).c_str(), 7, 0);
    hw->lcd->printText(currentModality == AUTOMATIC ? "Automatic" : "Manual", 10, 1);
}