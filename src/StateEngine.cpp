#include "StateEngine.h"

StateEngine::StateEngine(MotionSensor& pir, RampedServo& yaw, RampedServo& pitch, RampedServo& jaw, RampedServo& eye, AudioController& mp3)
    : currentState(STATE_IDLE),
      stateStartTime(0),
      lastEyeMoveTime(0),
      lastJawMoveTime(0),
      sequenceDuration(20000), // 20-second sequence duration
      sensor(pir),
      yawServo(yaw),
      pitchServo(pitch),
      jawServo(jaw),
      eyeServo(eye),
      audio(mp3) {}

void StateEngine::begin() {
    sensor.begin();
    yawServo.begin(90);
    pitchServo.begin(95);
    jawServo.begin(55); // Closed mouth home
    eyeServo.begin(90);  // Centered eyes home
    audio.begin();
    audio.setVolume(20); // Scale volume to 20/30
    currentState = STATE_IDLE;
}

void StateEngine::update() {
    // Update all servo ramp profiles
    yawServo.update();
    pitchServo.update();
    jawServo.update();
    eyeServo.update();

    switch (currentState) {
        case STATE_IDLE:
            handleIdle();
            break;
        case STATE_TRIGGERED:
            handleTriggered();
            break;
        case STATE_SPEAKING:
            handleSpeaking();
            break;
        case STATE_HYDRAULIC_TILT:
            handleHydraulicTilt();
            break;
        case STATE_RETURN_TO_HOME:
            handleReturnToHome();
            break;
        case STATE_REST_COOLDOWN:
            handleRestCooldown();
            break;
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
    audio.playTrack(1, 1); // Folder 01, Track 001 (Harriet Tubman Narrator File)
    stateStartTime = millis();
    lastEyeMoveTime = stateStartTime;
    lastJawMoveTime = stateStartTime;
    currentState = STATE_SPEAKING;
}

void StateEngine::handleSpeaking() {
    uint32_t currentTime = millis();
    
    updateEyeSaccades();
    updateJawSpeechSync();

    // Slow scanning pan movement (Yaw)
    if (currentTime - stateStartTime < 8000) {
        yawServo.setTarget(110);
    } else if (currentTime - stateStartTime < 14000) {
        yawServo.setTarget(70);
    } else {
        yawServo.setTarget(90);
    }

    // After 15 seconds of speaking, transition to the hydraulic lift tilt phase
    if ((currentTime - stateStartTime) >= 15000) {
        currentState = STATE_HYDRAULIC_TILT;
        pitchServo.setTarget(125); // Drive syringes to tilt neck up
    }
}

void StateEngine::handleHydraulicTilt() {
    uint32_t currentTime = millis();
    
    updateEyeSaccades();
    updateJawSpeechSync();

    // Pan head left and right slightly while tilted up
    if (currentTime - stateStartTime < 18000) {
        yawServo.setTarget(100);
    } else {
        yawServo.setTarget(80);
    }

    // Complete the full speaking script sequence after 25 seconds
    if ((currentTime - stateStartTime) >= 25000) {
        currentState = STATE_RETURN_TO_HOME;
        yawServo.setTarget(90);
        pitchServo.setTarget(95); // Release pressure to drop neck down
        jawServo.setTarget(55);  // Close jaw
        eyeServo.setTarget(90);  // Center eyes
    }
}

void StateEngine::handleReturnToHome() {
    // Wait for mechanical systems to completely return to home coordinates
    if (yawServo.isAtTarget() && pitchServo.isAtTarget() && 
        jawServo.isAtTarget() && eyeServo.isAtTarget()) {
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

void StateEngine::updateEyeSaccades() {
    uint32_t currentTime = millis();
    
    // Shift eyes to a new random target every 1.5 to 3 seconds to simulate scanning
    if ((currentTime - lastEyeMoveTime) >= 2000) {
        lastEyeMoveTime = currentTime;
        uint8_t randomAngle = random(60, 120); // Bound range centered at 90
        eyeServo.setTarget(randomAngle);
    }
}

void StateEngine::updateJawSpeechSync() {
    uint32_t currentTime = millis();
    
    // Sync jaw mouth flaps in intervals mimicking human speech syllables
    if ((currentTime - lastJawMoveTime) >= 120) {
        lastJawMoveTime = currentTime;
        
        // Randomly pick closed, partially open, or fully open mouth coordinates
        uint8_t jawState = random(0, 3);
        if (jawState == 0) {
            jawServo.setTarget(55); // Mouth fully closed
        } else if (jawState == 1) {
            jawServo.setTarget(70); // Semi-open mouth
        } else {
            jawServo.setTarget(85); // Fully open mouth
        }
    }
}

SystemState StateEngine::getCurrentState() const {
    return currentState;
}
