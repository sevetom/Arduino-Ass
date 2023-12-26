#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin) {
    this->sonar = new NewPing(trigPin, echoPin, PING_TIME);
}

int Sonar::getDistance() {
    return this->sonar->ping_cm();
}