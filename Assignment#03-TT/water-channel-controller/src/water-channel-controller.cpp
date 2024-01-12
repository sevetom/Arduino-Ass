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
int serialRead();
/**
 * @brief Print the status of the system
*/
void printStatus();

volatile modality currentModality;
volatile char currentAngle;
Components* hw;

void setup() {
    Serial.begin(9600);
    Components* hw = new Components();
    currentModality = AUTOMATIC;
    currentAngle = 0;
    hw->button->setInterrupt(changeModality, true);
    hw->lcd->printText("Modality: ", 0, 1);
    hw->lcd->printText("Angle: ", 0, 0);
}

void loop() {
    int value = INVALID;
    noInterrupts();
    switch (currentModality) {
        case AUTOMATIC:
            value = serialRead();
            break;
        case MANUAL:
            value = hw->pot->detectChange() ? hw->pot->getValue() : INVALID;
            break;
    }
    interrupts();
    if (value >= 0) {
        Serial.println("Value: " + String(value));
        delay(100);
        currentAngle = map(value, MIN_PERC, MAX_PERC, hw->gate->getMinAngle(), hw->gate->getMaxAngle());
        Serial.println("Angle: " + String(currentAngle));
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

int serialRead() {
    const int BUFFER_SIZE = 10;
    char buffer[BUFFER_SIZE];
    int index = 0;
    int length = 0;
    while (Serial.available() > 0 && index < BUFFER_SIZE - 1) {
        if (length == 0) {
            char tmp = Serial.read();
            length = tmp - '0';
            Serial.println("Length: " + String(length));
        }
        char nextChar = Serial.read();
        buffer[index] = nextChar;
        index++;
        Serial.println("Index: " + String(index));
        if (index == length) {
            buffer[index] = '\0';
            Serial.println("Buffer: " + String(buffer));
            return atoi(buffer);
        }
    }
    return INVALID;
}

void printStatus() {
    hw->lcd->printText(String(currentAngle).c_str(), 7, 0);
    hw->lcd->printText(currentModality == AUTOMATIC ? "Automatic" : "Manual", 10, 1);
}