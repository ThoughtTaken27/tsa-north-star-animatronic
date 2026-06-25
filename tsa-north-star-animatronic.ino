/*
 * "The North Star" — Harriet Tubman Animatronic Bust Firmware
 * 
 * Target Board: Arduino Uno R3 / ATmega328P
 * Development Platform: Arduino IDE / C++
 * 
 * Description: Coordinates sensor polling, audio, and motor controls
 * using a fully non-blocking, asynchronous finite state machine (FSM).
 * 
 * Author: Parth Khavate (Systems Integrator / Team Captain)
 * Completion Date: May 2026 — 1st Place Tennessee State Championship
 */

#include "firmware/Sensors.h"
#include "firmware/Actuators.h"
#include "firmware/AudioController.h"
#include "firmware/StateEngine.h"

// --- Pin Allocations (See hardware/bom.md) ---
const uint8_t PIN_PIR_SENSOR = 2;   // Input from PIR sensor
const uint8_t PIN_NECK_YAW   = 5;   // PWM Output to Neck Yaw MG996R
const uint8_t PIN_NECK_PITCH = 6;   // PWM Output to Neck Pitch MG996R
const uint8_t PIN_JAW_MOVE   = 9;   // PWM Output to Jaw Move MG996R
const uint8_t PIN_AUDIO_RX   = 10;  // Software RX Pin (TX on DFPlayer)
const uint8_t PIN_AUDIO_TX   = 11;  // Software TX Pin (RX on DFPlayer via 1kΩ)
const uint8_t PIN_EYE_MOVE   = 12;  // Digital I/O to Eye Move SG90

// --- Instantiations ---
MotionSensor motionDetector(PIN_PIR_SENSOR, 150); // 150ms temporal debounce filter

// Ramped servos with custom hardware safe angle boundaries (min, max, speed scale)
RampedServo neckYawServo(PIN_NECK_YAW, 30, 150, 1.2);
RampedServo neckPitchServo(PIN_NECK_PITCH, 50, 140, 0.8); // Hydraulic slow lift
RampedServo jawServo(PIN_JAW_MOVE, 20, 90, 2.5);          // Fast mouth snap
RampedServo eyeServo(PIN_EYE_MOVE, 45, 135, 1.5);

AudioController audioController(PIN_AUDIO_RX, PIN_AUDIO_TX);

StateEngine showSequencer(
    motionDetector, 
    neckYawServo, 
    neckPitchServo, 
    jawServo, 
    eyeServo, 
    audioController
);

void setup() {
    // Start hardware serial for diagnostic logging output
    Serial.begin(115200);
    Serial.println(F("[SYSTEM INF]: Initializing \"The North Star\" Animatronic..."));

    // Set random seed based on noise from floating analog pin A0 for eye/mouth randomness
    randomSeed(analogRead(A0));

    // Initialize FSM modules and drive systems
    showSequencer.begin();
    
    Serial.println(F("[SYSTEM INF]: Startup complete. FSM state set to STATE_IDLE."));
    Serial.println(F("[SYSTEM INF]: Awaiting PIR motion trigger..."));
}

void loop() {
    // Main loop must remain non-blocking. Individual update calls
    // execute speed step tracking and polling based on internal millis() timers.
    showSequencer.update();
    
    // Diagnostic output stream (conditional based on state transitions)
    static SystemState lastState = STATE_REST_COOLDOWN;
    SystemState currentState = showSequencer.getCurrentState();
    
    if (currentState != lastState) {
        lastState = currentState;
        Serial.print(F("[FSM STATE CHANGE]: New state is "));
        switch (currentState) {
            case STATE_IDLE:             Serial.println(F("STATE_IDLE"));             break;
            case STATE_TRIGGERED:        Serial.println(F("STATE_TRIGGERED"));        break;
            case STATE_SPEAKING:         Serial.println(F("STATE_SPEAKING"));         break;
            case STATE_HYDRAULIC_TILT:   Serial.println(F("STATE_HYDRAULIC_TILT"));   break;
            case STATE_RETURN_TO_HOME:   Serial.println(F("STATE_RETURN_TO_HOME"));   break;
            case STATE_REST_COOLDOWN:    Serial.println(F("STATE_REST_COOLDOWN"));    break;
        }
    }
}
