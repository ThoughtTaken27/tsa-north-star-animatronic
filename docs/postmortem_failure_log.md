# Engineering Failure Log - "The North Star"

This postmortem records the real failure modes that mattered during the build. It intentionally avoids unsupported lab-style details such as exact oscilloscope readings or custom-machined parts.

## 1. Servo Power Resets

**Symptom:** The Arduino would reset or behave unpredictably when multiple servos moved.

**Cause:** The servo rail pulled more current than the Arduino logic rail could tolerate when everything shared power too closely.

**Fix:**

- Powered servos from a separate 4xAA pack.
- Kept Arduino logic on its own 9V input.
- Tied all grounds together so signal references stayed consistent.
- Added a 1000 uF capacitor across the servo power rail to reduce brief voltage dips.

## 2. PIR Sensor False Triggers

**Symptom:** The HC-SR501 triggered immediately after power-on or fired when nobody was intentionally activating the exhibit.

**Cause:** The PIR sensor needed time to stabilize, and its sensitivity setting was not initially tuned for the room and wiring conditions.

**Fix:**

- Tuned the sensitivity potentiometer.
- Added a 60-second startup warm-up lock in the firmware.
- Kept a cooldown after each show cycle so the sequence would not restart instantly.

## 3. Syringe Tubing Leaks and Slippage

**Symptom:** The fluid line leaked or slipped off when the controller syringe was pushed.

**Cause:** The first tubing fit was too loose for reliable pressure transfer.

**Fix:**

- Used 3/16 in tubing that fit tightly on the syringe tips.
- Secured the tubing at the syringe ends.
- Tested the line under repeated servo cycles before hiding it under the presentation layer.

## 4. Air Bubbles in the Fluid Line

**Symptom:** The hydraulic arm moved weakly or inconsistently.

**Cause:** Air trapped in the line compressed under load, making the actuator feel springy instead of transferring motion cleanly.

**Fix:**

- Filled and cycled the line slowly.
- Tapped the tubing while moving the syringe to release bubbles.
- Re-tested until the arm rose consistently.

## 5. Linkage Geometry Binding

**Symptom:** The syringe-driven arm stalled or moved sideways instead of rising cleanly.

**Cause:** The syringe plunger and arm linkage were not aligned. The servo was pushing at an angle, wasting torque and binding the plunger.

**Fix:**

- Repositioned the controller syringe.
- Adjusted the servo horn linkage.
- Added pivot freedom where needed so the arm could rotate instead of forcing the plunger sideways.

## 6. DFPlayer Mini Wiring and SD Card Setup

**Symptom:** The DFPlayer failed to play narration during early tests.

**Causes:**

- The DFPlayer RX line needed a safer logic-level input from the Arduino TX pin.
- The SD card and file naming had to match the DFPlayer command being used.

**Fix:**

- Used a 680 ohm / 1k ohm voltage divider on Arduino `D2` to DFPlayer RX.
- Formatted the microSD card as FAT32.
- Put the narration in `/mp3/0001_harriet.mp3`.
- Updated the firmware to use the DFPlayer command for numbered files in the `/mp3` folder.

## 7. Competition-Day Backdrop Recovery

**Event:** During setup, the team realized the painted black star backdrop had been left in the nearby hotel room.

**Response:** One teammate retrieved the backdrop while the others continued setup, powered the electronics, and let the PIR warm-up period run.

**Outcome:** The exhibit was ready within the setup window. Judge feedback highlighted that the project was self-contained and did not need to remain plugged into a laptop during the presentation.
