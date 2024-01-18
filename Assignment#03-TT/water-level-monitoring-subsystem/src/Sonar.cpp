#include "Sonar.h"

Sonar::Sonar(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->sonar = new NewPing(trigPin, echoPin, PING_TIME);
}

float Sonar::getDistance() {
    digitalWrite(this->trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin, LOW);
    float tUS = pulseIn(this->echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t * (331.45 + 0.62 * 20);
    return d * 100;
}