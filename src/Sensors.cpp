#include "Sensors.h"

MotionSensor::MotionSensor(uint8_t inputPin, uint32_t debounceMs) 
    : pin(inputPin), 
      debounceDuration(debounceMs), 
      lastStateChangeTime(0), 
      lastRawState(LOW), 
      lastDebouncedState(LOW) {}

void MotionSensor::begin() {
    pinMode(pin, INPUT);
    lastRawState = digitalRead(pin);
    lastDebouncedState = lastRawState;
}

bool MotionSensor::update() {
    bool currentState = digitalRead(pin);
    uint32_t currentTime = millis();

    // Reset timer if raw state toggled
    if (currentState != lastRawState) {
        lastStateChangeTime = currentTime;
        lastRawState = currentState;
    }

    // Verify if state has been steady for the required duration
    if ((currentTime - lastStateChangeTime) >= debounceDuration) {
        if (currentState != lastDebouncedState) {
            lastDebouncedState = currentState;
            // Return true only when state transitions to active (HIGH)
            if (lastDebouncedState == HIGH) {
                return true;
            }
        }
    }
    return false;
}

bool MotionSensor::isTriggered() const {
    return lastDebouncedState == HIGH;
}
