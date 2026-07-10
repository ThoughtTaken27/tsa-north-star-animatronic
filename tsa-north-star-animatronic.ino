/*
 * "The North Star" — Harriet Tubman Animatronic Bust Firmware
 * 
 * Target Board: Arduino Uno R3 / ATmega328P
 * Development Platform: Arduino IDE / C++
 * 
 * Description: Coordinates PIR triggering, audio playback, LEDs, and
 * servo-driven motion using a non-blocking finite state machine (FSM).
 * 
 * Author: Parth Khavate (Systems Integrator / Team Captain)
 * State Competition: April 2026 — 1st Place Tennessee State Championship
 */

#include "src/Sensors.h"
#include "src/Actuators.h"
#include "src/AudioController.h"
#include "src/StateEngine.h"

// --- Pin Allocations (See hardware/bom.md) ---
const uint8_t PIN_AUDIO_TX        = 3;   // Arduino TX -> DFPlayer RX through 680Ω/1kΩ divider
const uint8_t PIN_AUDIO_RX        = 2;   // Arduino RX <- DFPlayer TX
const uint8_t PIN_NORTH_STAR_LED  = 4;   // Orange/amber North Star LED through 220Ω
const uint8_t PIN_LANTERN_LED     = 5;   // Warm white lantern LED through 220Ω
const uint8_t PIN_SYRINGE_ARM     = 6;   // MG996R driving right-side syringe linkage
const uint8_t PIN_PIR_SENSOR      = 7;   // HC-SR501 PIR sensor OUT
const uint8_t PIN_HEAD_TURN       = 9;   // MG996R head turn servo
const uint8_t PIN_LANTERN_ARM     = 11;  // SG90 lantern arm servo

// --- Instantiations ---
MotionSensor motionDetector(PIN_PIR_SENSOR, 150); // 150ms temporal debounce filter

// Ramped servos with custom hardware safe angle boundaries (min, max, speed scale)
RampedServo headTurnServo(PIN_HEAD_TURN, 55, 125, 1.2);
RampedServo syringeArmServo(PIN_SYRINGE_ARM, 40, 130, 0.7);
RampedServo lanternArmServo(PIN_LANTERN_ARM, 60, 125, 1.0);

AudioController audioController(PIN_AUDIO_RX, PIN_AUDIO_TX);

StateEngine showSequencer(
    motionDetector, 
    headTurnServo,
    syringeArmServo,
    lanternArmServo,
    audioController,
    PIN_NORTH_STAR_LED,
    PIN_LANTERN_LED
);

void setup() {
    // Start hardware serial for diagnostic logging output
    Serial.begin(115200);
    Serial.println(F("[SYSTEM INF]: Initializing \"The North Star\" Animatronic..."));

    // Seed any future randomized motion from a floating analog pin.
    randomSeed(analogRead(A0));

    // Initialize FSM modules and drive systems
    showSequencer.begin();
    
    Serial.println(F("[SYSTEM INF]: Startup complete. PIR warm-up lock active."));
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
            case STATE_SENSOR_WARMUP:    Serial.println(F("STATE_SENSOR_WARMUP"));    break;
            case STATE_IDLE:             Serial.println(F("STATE_IDLE"));             break;
            case STATE_TRIGGERED:        Serial.println(F("STATE_TRIGGERED"));        break;
            case STATE_SPEAKING:         Serial.println(F("STATE_SPEAKING"));         break;
            case STATE_GESTURE:          Serial.println(F("STATE_GESTURE"));          break;
            case STATE_RETURN_TO_HOME:   Serial.println(F("STATE_RETURN_TO_HOME"));   break;
            case STATE_REST_COOLDOWN:    Serial.println(F("STATE_REST_COOLDOWN"));    break;
        }
    }
}
