/*
 * "The North Star" — Harriet Tubman Animatronic Bust Firmware
 * (COMPETITION VERSION — the code that actually ran on the Arduino)
 *
 * Target Board: Arduino Uno R3 / ATmega328P
 *
 * This is the ACTUAL blocking firmware used at the Tennessee TSA State
 * Leadership Conference on April 10, 2026. It was written collaboratively
 * and iterated across multiple sessions leading up to the competition.
 *
 * It differs from tsa-north-star-animatronic.ino (the modular repo version):
 *   * This build is BLOCKING: it drives the show with delay() calls in a
 *     single linear sequence, not a non-blocking millis() FSM.
 *   * It uses the DFRobotDFPlayerMini library for audio control.
 *   * The hydraulic arm waits a precise number of seconds after audio
 *     starts before moving (synced to the narration).
 *   * The North Star LED stays ON between rounds (beacon effect).
 *   * The lantern LED turns OFF during the outro.
 *   * It has a DFPlayer-presence fallback so lights/motion still run
 *     if the audio module is missing.
 *
 * Pin allocations:
 *   D2    - Arduino RX (SoftwareSerial) <- DFPlayer TX (direct)
 *   D3    - Arduino TX (SoftwareSerial) -> DFPlayer RX (through 680/1k divider)
 *   D4    - North Star LED (orange, through 220 ohm)
 *   D5    - Lantern LED (warm white, through 220 ohm)
 *   D6    - Syringe-drive servo (MG996R)
 *   D7    - PIR sensor OUT
 *   D9    - Head turn servo (MG996R)
 *   D11   - Lantern arm servo (SG90)
 *
 * Author: Parth Khavate (Systems Integrator / Team Captain)
 * State Competition: April 2026 — 1st Place Tennessee State Championship
 */

#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(2, 3);
DFRobotDFPlayerMini myDFPlayer;

Servo headServo;
Servo leftArmServo;
Servo hydraulicServo;

// ==========================
// PIN SETUP
// ==========================
const int pirPin = 7;
const int lanternPin = 5;
const int starPin = 4;

// ==========================
// HEAD SETTINGS (Pin 9)
// ==========================
int headAway = 90;
int headForward = 60;

// ==========================
// LEFT ARM SETTINGS (Pin 11)
// ==========================
int leftDown = 0;
int leftUp = 90;

// ==========================
// HYDRAULIC SETTINGS (Pin 6)
// ==========================
int hydroRest = 70;
int hydroPush = 18;

// IMPORTANT:
// If this grinds, try 19, then 20, then 21.
// Do NOT go lower unless you KNOW it is safe.

// ==========================
// AUDIO SETTINGS
// ==========================
int audioLengthSeconds = 33;
int volumeLevel = 30;

// ==========================
// MOVEMENT SPEEDS
// ==========================
int headSpeed = 20;        // lower number = faster
int leftArmSpeed = 20;
int hydraulicSpeed = 35;   // slightly slower helps fluid power

// ==========================
// SYSTEM FLAGS
// ==========================
bool audioReady = false;
bool canTrigger = true;

// ==========================
// SMOOTH SERVO MOVE
// ==========================
void moveServoSmooth(Servo &myServo, int startAngle, int endAngle, int stepDelay) {
  if (startAngle < endAngle) {
    for (int a = startAngle; a <= endAngle; a++) {
      myServo.write(a);
      delay(stepDelay);
    }
  } else {
    for (int a = startAngle; a >= endAngle; a--) {
      myServo.write(a);
      delay(stepDelay);
    }
  }
}

// ==========================
// MAIN SHOW SEQUENCE
// ==========================
void runSequence() {
  Serial.println("MOTION DETECTED! Starting sequence...");

  // RESET — turn both lights OFF briefly before each new round
  digitalWrite(lanternPin, LOW);
  digitalWrite(starPin, LOW);
  delay(600);

  // STEP 1: Lantern turns on
  digitalWrite(lanternPin, HIGH);
  delay(500);

  // STEP 2: Head turns toward visitor
  Serial.println("Head turning...");
  moveServoSmooth(headServo, headAway, headForward, headSpeed);
  delay(200);

  // STEP 3: Audio starts — CLOCK STARTS HERE
  unsigned long audioStartTime = millis();
  if (audioReady) {
    Serial.println("Playing audio...");
    myDFPlayer.playMp3Folder(1);
  } else {
    Serial.println("DFPlayer not ready. Running without audio.");
  }
  delay(500);

  // STEP 4: Left arm raises lantern
  Serial.println("Raising lantern...");
  moveServoSmooth(leftArmServo, leftDown, leftUp, leftArmSpeed);
  delay(200);

  // WAIT until exactly 18 seconds after audio started
  unsigned long hydraulicTargetTime = audioStartTime + 18000UL;
  unsigned long nowTime = millis();
  if (nowTime < hydraulicTargetTime) {
    delay(hydraulicTargetTime - nowTime);
  }

  // STEP 5: Hydraulic arm points upward
  Serial.println("Hydraulic arm moving...");
  moveServoSmooth(hydraulicServo, hydroRest, hydroPush, hydraulicSpeed);
  delay(200);

  // STEP 6: North Star turns on
  digitalWrite(starPin, HIGH);
  Serial.println("North Star ON.");

  // STEP 7: Wait until 5 seconds before audio ends, then begin outro
  unsigned long totalAudioMs = (unsigned long)audioLengthSeconds * 1000UL;
  unsigned long outroTargetTime = audioStartTime + totalAudioMs - 5000UL;
  unsigned long nowTime2 = millis();
  if (nowTime2 < outroTargetTime) {
    delay(outroTargetTime - nowTime2);
  }

  // STEP 8: Outro begins
  Serial.println("Outro starting...");

  // Lower left arm
  moveServoSmooth(leftArmServo, leftUp, leftDown, leftArmSpeed);
  delay(200);

  // Head turns away
  moveServoSmooth(headServo, headForward, headAway, headSpeed);
  delay(200);

  // Lantern OFF — turns off at outro
  digitalWrite(lanternPin, LOW);
  delay(200);

  // STEP 9: Hydraulic servo returns to rest
  Serial.println("Returning hydraulic servo to rest...");
  moveServoSmooth(hydraulicServo, hydroPush, hydroRest, hydraulicSpeed);
  delay(200);

  // NOTE: Star stays ON — glowing until next visitor

  // Safety stop for audio
  if (audioReady) {
    myDFPlayer.stop();
  }

  Serial.println("Sequence complete. North Star staying ON until next visitor.");

  // Wait until sensor goes LOW before allowing next trigger
  while (digitalRead(pirPin) == HIGH) {
    delay(50);
  }

  delay(500);
  Serial.println("Ready for next visitor.");
}

// ==========================
// SETUP
// ==========================
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(pirPin, INPUT);
  pinMode(lanternPin, OUTPUT);
  pinMode(starPin, OUTPUT);

  // Both lights off at startup
  digitalWrite(lanternPin, LOW);
  digitalWrite(starPin, LOW);

  // Set positions BEFORE attach to prevent startup jump
  headServo.write(headAway);
  headServo.attach(9);

  leftArmServo.write(leftDown);
  leftArmServo.attach(11);

  hydraulicServo.write(hydroRest);
  hydraulicServo.attach(6);

  // Give DFPlayer time to wake up
  delay(1000);

  Serial.println("Starting DFPlayer...");
  if (myDFPlayer.begin(mySerial)) {
    audioReady = true;
    myDFPlayer.volume(volumeLevel);
    Serial.println("DFPlayer ready.");
  } else {
    audioReady = false;
    Serial.println("WARNING: DFPlayer not found. Lights and movement will still work.");
  }

  // PIR calibration — 60 seconds
  Serial.println("============================");
  Serial.println("CALIBRATING... LEAVE THE ROOM!");
  Serial.println("============================");

  for (int i = 60; i > 0; i--) {
    Serial.print(i);
    Serial.println(" seconds...");
    delay(1000);
  }

  Serial.println("SYSTEM READY. WALK UP TO THE SENSOR.");
}

// ==========================
// LOOP
// ==========================
void loop() {
  int motion = digitalRead(pirPin);

  if (motion == HIGH && canTrigger == true) {
    canTrigger = false;
    runSequence();
  }

  if (motion == LOW) {
    canTrigger = true;
  }
}
