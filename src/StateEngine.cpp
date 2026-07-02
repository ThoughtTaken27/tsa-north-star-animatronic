#include "StateEngine.h"

StateEngine::StateEngine(MotionSensor& pir, RampedServo& head, RampedServo& syringe, RampedServo& lantern, AudioController& mp3, uint8_t starLed, uint8_t lanternLed)
    : currentState(STATE_SENSOR_WARMUP),
      stateStartTime(0),
      sequenceDuration(75000), // Narration target: roughly 75 seconds
      sensor(pir),
      headServo(head),
      syringeServo(syringe),
      lanternServo(lantern),
      audio(mp3),
      northStarLedPin(starLed),
      lanternLedPin(lanternLed) {}

void StateEngine::begin() {
    pinMode(northStarLedPin, OUTPUT);
    pinMode(lanternLedPin, OUTPUT);
    digitalWrite(northStarLedPin, LOW);
    digitalWrite(lanternLedPin, LOW);

    sensor.begin();
    headServo.begin(90);
    syringeServo.begin(45); // Arm down / syringe home
    lanternServo.begin(70);   // Lantern resting near body
    audio.begin();
    audio.setVolume(20); // Scale volume to 20/30
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
    if ((millis() - stateStartTime) >= 60000) {
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
    audio.playMp3Track(1); // /mp3/0001_harriet.mp3
    stateStartTime = millis();
    digitalWrite(lanternLedPin, HIGH);
    headServo.setTarget(105);
    lanternServo.setTarget(95);
    currentState = STATE_SPEAKING;
}

void StateEngine::handleSpeaking() {
    uint32_t currentTime = millis();
    uint32_t elapsed = currentTime - stateStartTime;
    
    // Slow head scan while the narration begins.
    if (elapsed < 12000) {
        headServo.setTarget(105);
    } else if (elapsed < 22000) {
        headServo.setTarget(75);
    } else {
        headServo.setTarget(90);
    }

    if (elapsed >= 30000) {
        currentState = STATE_GESTURE;
        syringeServo.setTarget(125); // Drive syringe linkage to move right arm
        lanternServo.setTarget(120);
        digitalWrite(northStarLedPin, HIGH);
    }
}

void StateEngine::handleGesture() {
    uint32_t currentTime = millis();
    uint32_t elapsed = currentTime - stateStartTime;

    // Keep the figure oriented toward the backdrop as the arm points.
    if (elapsed < 52000) {
        headServo.setTarget(80);
    } else {
        headServo.setTarget(95);
    }

    if (elapsed >= sequenceDuration) {
        currentState = STATE_RETURN_TO_HOME;
        headServo.setTarget(90);
        syringeServo.setTarget(45);
        lanternServo.setTarget(70);
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
    if ((currentTime - stateStartTime) >= 10000) {
        currentState = STATE_IDLE;
    }
}

SystemState StateEngine::getCurrentState() const {
    return currentState;
}
