#include <Arduino.h>
#include <Components.h>

typedef enum {
    AUTOMATIC,
    MANUAL
} modality;

void changeModality();
char serialRead();

volatile modality currentModality;
volatile long prevts = 0;

void setup() {
    Serial.begin(9600);
    Components* hw = new Components();
    currentModality = AUTOMATIC;
    hw->button->setInterrupt(changeModality, true);
}

void loop() {
    switch (currentModality) {
        case AUTOMATIC:
            Serial.println("Automatic");
            break;
        case MANUAL:
            Serial.println("Manual");
            break;
    }
}

void changeModality() {
    if (hw->button->avoidBouncing()) {
        currentModality = (currentModality == AUTOMATIC) ? MANUAL : AUTOMATIC;
    }
}

char serialRead() {
    while (Serial.available() > 0) {
        return Serial.read();
    }
}