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

// --- Sequence timing constants (all in milliseconds) ---
static const uint32_t PIR_WARMUP_MS        = 60000;  // HC-SR501 stabilization on power-on
static const uint32_t NARRATION_DURATION   = 33000;  // Total narration target length (33 seconds)
static const uint32_t SPEAKING_PHASE_1_MS   = 12000;  // Slow head scan toward viewer
static const uint32_t SPEAKING_PHASE_2_MS   = 22000;  // Head scan away
static const uint32_t GESTURE_TRIGGER_MS    = 18000;  // When to raise arm + light North Star (18s after audio)
static const uint32_t GESTURE_HEAD_TURN_MS   = 52000;  // Head reorientation during gesture
static const uint32_t REST_COOLDOWN_MS       = 10000;  // Prevent rapid re-trigger

// --- Servo angle targets ---
static const uint8_t HEAD_HOME              = 90;
static const uint8_t HEAD_SPEAK_RIGHT       = 105;
static const uint8_t HEAD_SPEAK_LEFT        = 75;
static const uint8_t HEAD_GESTURE_AWAY      = 80;
static const uint8_t HEAD_GESTURE_RETURN    = 95;
static const uint8_t SYRINGE_HOME           = 45;
static const uint8_t SYRINGE_ACTIVE          = 125;
static const uint8_t LANTERN_HOME           = 70;
static const uint8_t LANTERN_SPEAK          = 95;
static const uint8_t LANTERN_GESTURE        = 120;

// --- Audio settings ---
static const uint8_t DFPLAYER_VOLUME        = 20;     // Scale: 0-30

class StateEngine {
private:
    SystemState currentState;
    uint32_t stateStartTime;
    uint32_t sequenceDuration;
    
    MotionSensor& sensor;
    RampedServo& headServo;
    RampedServo& syringeServo;
    RampedServo& lanternServo;
    AudioController& audio;
    uint8_t northStarLedPin;
    uint8_t lanternLedPin;
    uint8_t lastHeadTarget;
    uint8_t lastLanternTarget;

    void handleSensorWarmup();
    void handleIdle();
    void handleTriggered();
    void handleSpeaking();
    void handleGesture();
    void handleReturnToHome();
    void handleRestCooldown();

public:
    StateEngine(MotionSensor& pir, RampedServo& head, RampedServo& syringe, RampedServo& lantern, AudioController& mp3, uint8_t starLed, uint8_t lanternLed);
    void begin();
    void update(); // Must be called continuously in the loop to drive the FSM
    SystemState getCurrentState() const;
};

#endif
