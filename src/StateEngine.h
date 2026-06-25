#ifndef STATE_ENGINE_H
#define STATE_ENGINE_H

#include <Arduino.h>
#include "Sensors.h"
#include "Actuators.h"
#include "AudioController.h"

enum SystemState {
    STATE_IDLE,
    STATE_TRIGGERED,
    STATE_SPEAKING,
    STATE_HYDRAULIC_TILT,
    STATE_RETURN_TO_HOME,
    STATE_REST_COOLDOWN
};

class StateEngine {
private:
    SystemState currentState;
    uint32_t stateStartTime;
    uint32_t lastEyeMoveTime;
    uint32_t lastJawMoveTime;
    uint32_t sequenceDuration;
    
    MotionSensor& sensor;
    RampedServo& yawServo;
    RampedServo& pitchServo;
    RampedServo& jawServo;
    RampedServo& eyeServo;
    AudioController& audio;

    void handleIdle();
    void handleTriggered();
    void handleSpeaking();
    void handleHydraulicTilt();
    void handleReturnToHome();
    void handleRestCooldown();

    void updateEyeSaccades();
    void updateJawSpeechSync();

public:
    StateEngine(MotionSensor& pir, RampedServo& yaw, RampedServo& pitch, RampedServo& jaw, RampedServo& eye, AudioController& mp3);
    void begin();
    void update(); // Must be called continuously in the loop to drive the FSM
    SystemState getCurrentState() const;
};

#endif
