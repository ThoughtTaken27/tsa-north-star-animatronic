#include "StateEngine.h"

StateEngine::StateEngine(MotionSensor& pir, RampedServo& head, RampedServo& syringe, RampedServo& lantern, AudioController& mp3, uint8_t starLed, uint8_t lanternLed)
    : currentState(STATE_SENSOR_WARMUP),
      stateStartTime(0),
      sequenceDuration(NARRATION_DURATION),
      sensor(pir),
      headServo(head),
      syringeServo(syringe),
      lanternServo(lantern),
      audio(mp3),
      northStarLedPin(starLed),
      lanternLedPin(lanternLed),
      lastHeadTarget(HEAD_HOME),
      lastLanternTarget(LANTERN_HOME) {}

void StateEngine::begin() {
    pinMode(northStarLedPin, OUTPUT);
    pinMode(lanternLedPin, OUTPUT);
    digitalWrite(northStarLedPin, LOW);
    digitalWrite(lanternLedPin, LOW);

    sensor.begin();
    headServo.begin(HEAD_HOME);
    syringeServo.begin(SYRINGE_HOME);
    lanternServo.begin(LANTERN_HOME);
    audio.begin();
    audio.setVolume(DFPLAYER_VOLUME);
    currentState = STATE_SENSOR_WARMUP;
    stateStartTime = millis();
}

void StateEngine::update() {
    // Update all servo ramp profiles
    headServo.update();
    syringeServo.update();
    lanternServo.update();

    switch (currentState) {
        case STATE_SENSOR_WARMUP:
            handleSensorWarmup();
            break;
        case STATE_IDLE:
            handleIdle();
            break;
        case STATE_TRIGGERED:
            handleTriggered();
            break;
        case STATE_SPEAKING:
            handleSpeaking();
            break;
        case STATE_GESTURE:
            handleGesture();
            break;
        case STATE_RETURN_TO_HOME:
            handleReturnToHome();
            break;
        case STATE_REST_COOLDOWN:
            handleRestCooldown();
            break;
    }
}

void StateEngine::handleSensorWarmup() {
    // HC-SR501 modules can output unstable readings during initial calibration.
    if ((millis() - stateStartTime) >= PIR_WARMUP_MS) {
        currentState = STATE_IDLE;
    }
}

void StateEngine::handleIdle() {
    // Poll PIR sensor
    if (sensor.update()) {
        currentState = STATE_TRIGGERED;
        stateStartTime = millis();
    }
}

void StateEngine::handleTriggered() {
    audio.playMp3Track(1); // /mp3/0001.mp3
    stateStartTime = millis();
    digitalWrite(lanternLedPin, HIGH);
    headServo.setTarget(HEAD_SPEAK_RIGHT);
    lastHeadTarget = HEAD_SPEAK_RIGHT;
    lanternServo.setTarget(LANTERN_SPEAK);
    lastLanternTarget = LANTERN_SPEAK;
    currentState = STATE_SPEAKING;
}

void StateEngine::handleSpeaking() {
    uint32_t currentTime = millis();
    uint32_t elapsed = currentTime - stateStartTime;
    
    // Slow head scan while the narration begins.
    uint8_t newHeadTarget;
    if (elapsed < SPEAKING_PHASE_1_MS) {
        newHeadTarget = HEAD_SPEAK_RIGHT;
    } else if (elapsed < SPEAKING_PHASE_2_MS) {
        newHeadTarget = HEAD_SPEAK_LEFT;
    } else {
        newHeadTarget = HEAD_HOME;
    }
    // Only command the servo when the target actually changes
    if (newHeadTarget != lastHeadTarget) {
        headServo.setTarget(newHeadTarget);
        lastHeadTarget = newHeadTarget;
    }

    if (elapsed >= GESTURE_TRIGGER_MS) {
        currentState = STATE_GESTURE;
        syringeServo.setTarget(SYRINGE_ACTIVE);
        lanternServo.setTarget(LANTERN_GESTURE);
        lastLanternTarget = LANTERN_GESTURE;
        digitalWrite(northStarLedPin, HIGH);
    }
}

void StateEngine::handleGesture() {
    uint32_t currentTime = millis();
    uint32_t elapsed = currentTime - stateStartTime;

    // Keep the figure oriented toward the backdrop as the arm points.
    uint8_t newHeadTarget;
    if (elapsed < GESTURE_HEAD_TURN_MS) {
        newHeadTarget = HEAD_GESTURE_AWAY;
    } else {
        newHeadTarget = HEAD_GESTURE_RETURN;
    }
    if (newHeadTarget != lastHeadTarget) {
        headServo.setTarget(newHeadTarget);
        lastHeadTarget = newHeadTarget;
    }

    if (elapsed >= sequenceDuration) {
        currentState = STATE_RETURN_TO_HOME;
        headServo.setTarget(HEAD_HOME);
        lastHeadTarget = HEAD_HOME;
        syringeServo.setTarget(SYRINGE_HOME);
        lanternServo.setTarget(LANTERN_HOME);
        lastLanternTarget = LANTERN_HOME;
        digitalWrite(northStarLedPin, LOW);
        digitalWrite(lanternLedPin, LOW);
    }
}

void StateEngine::handleReturnToHome() {
    // Wait for mechanical systems to completely return to home coordinates
    if (headServo.isAtTarget() && syringeServo.isAtTarget() && lanternServo.isAtTarget()) {
        audio.stop();
        currentState = STATE_REST_COOLDOWN;
        stateStartTime = millis();
    }
}

void StateEngine::handleRestCooldown() {
    uint32_t currentTime = millis();
    
    // Hold system in inactive rest block for 10 seconds to prevent rapid trigger loop
    if ((currentTime - stateStartTime) >= REST_COOLDOWN_MS) {
        currentState = STATE_IDLE;
    }
}

SystemState StateEngine::getCurrentState() const {
    return currentState;
}
