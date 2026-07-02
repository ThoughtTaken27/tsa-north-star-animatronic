#ifndef STATE_ENGINE_H
#define STATE_ENGINE_H

#include <Arduino.h>
#include "Sensors.h"
#include "Actuators.h"
#include "AudioController.h"

enum SystemState {
    STATE_SENSOR_WARMUP,
    STATE_IDLE,
    STATE_TRIGGERED,
    STATE_SPEAKING,
    STATE_GESTURE,
    STATE_RETURN_TO_HOME,
    STATE_REST_COOLDOWN
};

class StateEngine {
private:
    SystemState currentState;
    uint32_t stateStartTime;
    uint32_t sequenceDuration;
    
    MotionSensor& sensor;
    RampedServo& headServo;
    RampedServo& hydraulicServo;
    RampedServo& lanternServo;
    AudioController& audio;
    uint8_t northStarLedPin;
    uint8_t lanternLedPin;

    void handleSensorWarmup();
    void handleIdle();
    void handleTriggered();
    void handleSpeaking();
    void handleGesture();
    void handleReturnToHome();
    void handleRestCooldown();

public:
    StateEngine(MotionSensor& pir, RampedServo& head, RampedServo& hydraulic, RampedServo& lantern, AudioController& mp3, uint8_t starLed, uint8_t lanternLed);
    void begin();
    void update(); // Must be called continuously in the loop to drive the FSM
    SystemState getCurrentState() const;
};

#endif
