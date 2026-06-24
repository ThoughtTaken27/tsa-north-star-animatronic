#include "Actuators.h"

RampedServo::RampedServo(uint8_t servoPin, uint8_t minLimit, uint8_t maxLimit, float speedScale)
    : pin(servoPin),
      currentAngle(90.0),
      targetAngle(90.0),
      stepIncrement(1.0 * speedScale),
      stepInterval(15), // Standard 15ms step update for 60Hz servo updates
      lastStepTime(0),
      minAngle(minLimit),
      maxAngle(maxLimit) {}

void RampedServo::begin(uint8_t initialAngle) {
    // Clamp to hardware boundaries
    initialAngle = constrain(initialAngle, minAngle, maxAngle);
    currentAngle = initialAngle;
    targetAngle = initialAngle;
    
    servoInstance.attach(pin);
    servoInstance.write(initialAngle);
    lastStepTime = millis();
}

void RampedServo::setTarget(uint8_t target) {
    targetAngle = constrain(target, minAngle, maxAngle);
}

void RampedServo::update() {
    uint32_t currentTime = millis();
    
    // Check if time step interval elapsed and target not yet reached
    if ((currentTime - lastStepTime) >= stepInterval) {
        lastStepTime = currentTime;
        
        if (currentAngle != targetAngle) {
            float diff = targetAngle - currentAngle;
            
            // Increment/decrement currentAngle toward target
            if (abs(diff) <= stepIncrement) {
                currentAngle = targetAngle;
            } else {
                if (diff > 0) {
                    currentAngle += stepIncrement;
                } else {
                    currentAngle -= stepIncrement;
                }
            }
            
            // Drive the servo hardware with calculated position
            servoInstance.write((uint8_t)round(currentAngle));
        }
    }
}

bool RampedServo::isAtTarget() const {
    return currentAngle == targetAngle;
}

uint8_t RampedServo::getPosition() const {
    return (uint8_t)round(currentAngle);
}

void RampedServo::forcePosition(uint8_t angle) {
    angle = constrain(angle, minAngle, maxAngle);
    currentAngle = angle;
    targetAngle = angle;
    servoInstance.write(angle);
}
