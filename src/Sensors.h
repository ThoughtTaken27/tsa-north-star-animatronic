#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class MotionSensor {
private:
    uint8_t pin;
    uint32_t debounceDuration;
    uint32_t lastStateChangeTime;
    bool lastSteadyState;
    bool lastDebouncedState;

public:
    MotionSensor(uint8_t inputPin, uint32_t debounceMs = 150);
    void begin();
    bool update(); // Must be called continuously in the loop, returns true on verified trigger
    bool isTriggered() const;
};

#endif
