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
 * @brief Read a line from the serial port
 * @param readch The character read from the serial port
 * @param buffer The buffer where the line will be stored
 * @param len The length of the buffer
 * @return The length of the line read
*/
int readline(int readch, char *buffer, int len);
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
        printStatus();
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
    char buf[3];
    if (readline(Serial.read(), buf, 3) > 0) {
        return atoi(buf);
    } else {
        return INVALID;
    }
}

int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;
    if (readch > 0) {
        switch (readch) {
            case '\r':
                break;
            case '\n':
                rpos = pos;
                pos = 0;
                return rpos;
            default:
                if (pos < len-1) {
                    buffer[pos++] = readch;
                    buffer[pos] = 0;
                }
        }
    }
    return 0;
}

void printStatus() {
    hw->lcd->printText(String(currentAngle).c_str(), 7, 0);
    hw->lcd->printText(currentModality == AUTOMATIC ? "Automatic" : "Manual", 10, 1);
}