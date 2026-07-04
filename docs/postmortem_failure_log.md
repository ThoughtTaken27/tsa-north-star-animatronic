# Engineering Failure Log - "The North Star"

This postmortem records the failures that actually shaped the final build: power stability, sensor reliability, audio playback, and the mechanical alignment of the exposed servo/syringe system.

## 1. Servo Power Resets

**Symptom:** The Arduino would reset or behave unpredictably when multiple servos moved.

**Cause:** The servos could pull enough current during movement to disturb the control electronics when power was not separated cleanly.

**Fix:**

- Powered servos from a separate switched 4xAA battery pack.
- Kept Arduino logic on its own 9V input.
- Tied all grounds together so signal references stayed consistent.
- Added a 1000 uF capacitor across the servo rail to reduce short voltage dips.

## 2. PIR Sensor False Triggers

**Symptom:** The HC-SR501 triggered immediately after power-on or fired when nobody was intentionally activating the exhibit.

**Cause:** The PIR sensor needed time to stabilize, and the on-board potentiometers and jumper were not correctly configured for the room and wiring conditions. The HiLetgo HC-SR501 modules have no printed pin labels, which meant the correct VCC-OUT-GND pinout had to be identified through systematic testing of all possible combinations before the sensor could be trusted.

**Fix:**

- Identified the correct pin order by exhaustive testing (VCC-OUT-GND, left to right with the dome facing you).
- Turned the sensitivity potentiometer fully clockwise (maximum sensitivity).
- Turned the time-delay potentiometer fully counter-clockwise (shortest output pulse, approximately 3 seconds).
- Moved the on-board jumper cap to the H position (repeatable trigger mode).
- Added a 60-second startup warm-up lock in the firmware so the sensor has time to learn the background infrared profile before accepting triggers.
- Kept a cooldown after each show cycle so the sequence would not restart instantly.

## 3. Syringe Linkage Binding

**Symptom:** The right-side syringe arm stalled, moved weakly, or pushed sideways instead of producing a clean gesture.

**Cause:** The syringe plunger and wooden linkage were sensitive to angle. When the servo horn pushed off-axis, the mechanism wasted torque and the plunger resisted motion.

**Fix:**

- Repositioned the syringe body and support point.
- Adjusted the MG996R servo horn and short wooden linkage.
- Added enough pivot freedom for the arm to move through its arc without forcing the syringe sideways.
- Reduced software travel limits so the servo stayed inside the reliable mechanical range.

## 4. Exposed Wiring Reliability

**Symptom:** Wires and servo leads could shift during testing, transport, or the removable-shell reveal.

**Cause:** The electronics were intentionally visible on the plywood base, which made the project easier to inspect but also exposed the wiring to bumps and pulls.

**Fix:**

- Routed wires along the PVC spine and base.
- Used zip ties to secure loose runs.
- Kept the Arduino, breadboard, DFPlayer, speaker, batteries, and PIR sensor accessible for inspection and troubleshooting.

## 5. DFPlayer Mini Wiring and SD Card Setup

**Symptom:** The DFPlayer failed to play narration during early tests.

**Causes:**

- The DFPlayer RX line needed a safer logic-level input from the Arduino TX pin.
- The SD card and file naming had to match the DFPlayer command being used.

**Fix:**

- Used a 680 ohm / 1k ohm voltage divider on Arduino `D2` to DFPlayer RX.
- Formatted the microSD card as FAT32.
- Put the narration in `/mp3/0001.mp3`.
- Ran `dot_clean` on the mounted SD card volume before ejecting from macOS to remove hidden `._` resource fork files that crash the DFPlayer.
- Updated the firmware to use the DFPlayer command for numbered files in the `/mp3` folder.

## 6. Competition-Day Backdrop Recovery

**Event:** During setup, the team realized the painted black star backdrop had been left in the nearby hotel room.

**Response:** One teammate retrieved the backdrop while the others continued setup, powered the electronics, and let the PIR warm-up period run.

**Outcome:** The exhibit was ready within the setup window. Judge feedback highlighted that the project was self-contained and did not need to remain plugged into a laptop during the presentation.
