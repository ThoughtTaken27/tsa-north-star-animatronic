/*
 * "The North Star" — Harriet Tubman Animatronic Bust Firmware
 * (RECOVERED / RECONSTRUCTED VERSION — see note below)
 *
 * Target Board: Arduino Uno R3 / ATmega328P
 *
 * RECOVERY NOTE
 * -------------
 * This sketch is a hand-reconstruction of the firmware that was physically
 * read back off the competition Arduino (flash dump dated 2026-07-06). The chip
 * cannot store C++ source, only compiled machine code, so this is NOT the
 * original source — it is a faithful behavioral equivalent derived by
 * disassembling the on-chip flash (avr-objdump) and tracing the loop() logic.
 *
 * It differs from tsa-north-star-animatronic.ino (the modular repo version):
 *   * This build is BLOCKING: it drives the show with delay() calls in a
 *     single linear sequence, not a non-blocking millis() FSM.
 *   * It prints human-readable narration strings (e.g. "Head turning...")
 *     rather than [FSM STATE CHANGE] debug names.
 *   * It refers to the arm as "hydraulic" and the reset phase as "outro".
 *   * It has a DFPlayer-presence fallback so lights/motion still run if the
 *     audio module is missing.
 *
 * Pin allocations (verified against the disassembly):
 *   D2/D3 - DFPlayer serial (TX/RX)
 *   D4    - North Star LED (amber)
 *   D5    - Lantern LED (warm white)
 *   D6    - Arm/syringe servo (MG996R)
 *   D7    - PIR sensor OUT
 *   D9    - Head turn servo (MG996R)
 *   D11   - Lantern arm servo (SG90)
 *
 * Author: Parth Khavate (Systems Integrator / Team Captain)
 * State Competition: April 2026 — 1st Place Tennessee State Championship
 */

#include <Servo.h>
#include <SoftwareSerial.h>

// --- Pin Allocations ---
const uint8_t PIN_AUDIO_TX        = 2;
const uint8_t PIN_AUDIO_RX        = 3;
const uint8_t PIN_NORTH_STAR_LED  = 4;
const uint8_t PIN_LANTERN_LED     = 5;
const uint8_t PIN_SYRINGE_ARM     = 6;
const uint8_t PIN_PIR_SENSOR      = 7;
const uint8_t PIN_HEAD_TURN       = 9;
const uint8_t PIN_LANTERN_ARM     = 11;

// --- Servos ---
Servo headServo;        // D9
Servo armServo;         // D6  (called "hydraulic arm" on the chip)
Servo lanternArmServo;  // D11

// --- Audio ---
SoftwareSerial mp3Serial(PIN_AUDIO_RX, PIN_AUDIO_TX); // RX, TX

bool dfPlayerReady = false;

// ----------------------------------------------------------------------------
// DFPlayer low-level packet (10-byte protocol, same as AudioController.cpp)
// ----------------------------------------------------------------------------
void dfPlayerSend(uint8_t command, uint16_t parameter) {
    uint8_t packet[10];
    packet[0] = 0x7E;
    packet[1] = 0xFF;
    packet[2] = 0x06;
    packet[3] = command;
    packet[4] = 0x00;
    packet[5] = (uint8_t)(parameter >> 8);
    packet[6] = (uint8_t)(parameter & 0xFF);
    uint16_t checksum = 0 - (packet[1] + packet[2] + packet[3] +
                              packet[4] + packet[5] + packet[6]);
    packet[7] = (uint8_t)(checksum >> 8);
    packet[8] = (uint8_t)(checksum & 0xFF);
    packet[9] = 0xEF;
    for (uint8_t i = 0; i < 10; i++) mp3Serial.write(packet[i]);
}

void dfPlayerReset()       { dfPlayerSend(0x0C, 0); }
void dfPlayerPlayMp3(uint16_t n) { dfPlayerSend(0x12, n); } // /mp3/000N_*.mp3
void dfPlayerStop()        { dfPlayerSend(0x16, 0); }
void dfPlayerVolume(uint8_t v)    { dfPlayerSend(0x06, constrain(v, 0, 30)); }

// ----------------------------------------------------------------------------
// setup()
// ----------------------------------------------------------------------------
void setup() {
    Serial.begin(115200);

    pinMode(PIN_NORTH_STAR_LED, OUTPUT);
    pinMode(PIN_LANTERN_LED, OUTPUT);
    pinMode(PIN_PIR_SENSOR, INPUT);

    // Servo attach (order recovered from setup() init table)
    headServo.attach(PIN_HEAD_TURN);
    armServo.attach(PIN_SYRINGE_ARM);
    lanternArmServo.attach(PIN_LANTERN_ARM);

    mp3Serial.begin(9600);

    // --- Calibration: drive all servos to home, tell viewer to step away ---
    headServo.write(90);      // head home
    armServo.write(0);        // arm/syringe home
    lanternArmServo.write(70); // lantern resting near body
    delay(1000);
    Serial.println(F("CALIBRATING... LEAVE THE ROOM!"));
    delay(1000);

    // --- DFPlayer presence check (recovered fallback behavior) ---
    dfPlayerReset();
    delay(500);
    // The chip polls for a response byte; if absent it flags not-ready.
    dfPlayerReady = (mp3Serial.available() > 0);
    if (dfPlayerReady) {
        Serial.println(F("Starting DFPlayer..."));
        dfPlayerVolume(20);
        Serial.println(F("DFPlayer ready."));
    } else {
        Serial.println(F("WARNING: DFPlayer not found. Lights and movement will still work."));
    }

    Serial.println(F("SYSTEM READY. WALK UP TO THE SENSOR."));
}

// ----------------------------------------------------------------------------
// loop() — blocking, linear sequence (matches the on-chip machine code)
// ----------------------------------------------------------------------------
void loop() {
    // Wait for PIR to go HIGH (polled in a tight loop)
    while (digitalRead(PIN_PIR_SENSOR) == LOW) {
        // idle
    }

    Serial.println(F("MOTION DETECTED! Starting sequence..."));

    // --- Lights + head turn ---
    digitalWrite(PIN_LANTERN_LED, HIGH);
    Serial.println(F("Head turning..."));
    headServo.write(85);     // turn head toward viewer
    lanternArmServo.write(70);
    delay(572);

    // --- Hydraulic arm / syringe gesture ---
    Serial.println(F("Hydraulic arm moving..."));
    armServo.write(90);      // drive syringe linkage
    digitalWrite(PIN_NORTH_STAR_LED, HIGH);
    delay(1000);

    // --- Lantern arm raise ---
    Serial.println(F("Raising lantern..."));
    lanternArmServo.write(70);
    delay(200);

    // --- Audio ---
    if (dfPlayerReady) {
        Serial.println(F("Playing audio..."));
        dfPlayerPlayMp3(1); // /mp3/0001_harriet.mp3
    } else {
        Serial.println(F("DFPlayer not ready. Running without audio."));
    }
    delay(200);

    // --- Outro: head back, return arm, lights off ---
    Serial.println(F("Outro starting..."));
    headServo.write(120);    // orient back toward backdrop
    armServo.write(0);       // return syringe to rest
    delay(200);

    Serial.println(F("Returning hydraulic servo to rest..."));
    armServo.write(0);
    digitalWrite(PIN_NORTH_STAR_LED, LOW);
    digitalWrite(PIN_LANTERN_LED, LOW);
    delay(200);

    Serial.println(F("Sequence complete. North Star staying ON until next visitor."));
    // North Star LED intentionally left controlled; arm/head return home
    headServo.write(90);

    Serial.println(F("Ready for next visitor."));
    delay(1000); // cooldown before re-arming the PIR poll
}
