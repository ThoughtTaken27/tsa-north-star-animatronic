#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <Arduino.h>
#include <Servo.h>

class RampedServo {
private:
    Servo servoInstance;
    uint8_t pin;
    float currentAngle;
    float targetAngle;
    float stepIncrement;     // Angle movement per step
    uint32_t stepInterval;   // Milliseconds between step increments
    uint32_t lastStepTime;   // Timestamp of last update step
    uint8_t minAngle;
    uint8_t maxAngle;

public:
    RampedServo(uint8_t servoPin, uint8_t minLimit, uint8_t maxLimit, float speedScale = 1.0);
    void begin(uint8_t initialAngle);
    void setTarget(uint8_t target);
    void update(); // Evaluates speed increments based on millis() non-blocking
    bool isAtTarget() const;
    uint8_t getPosition() const;
    void forcePosition(uint8_t angle);
};

#endif
