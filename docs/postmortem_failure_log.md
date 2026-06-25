# Engineering Postmortem & Failure Log — "The North Star"

This log documents the problems encountered during the build, what the actual cause was, and what fixed it. Captured from the build log maintained during the 8-week development cycle.

---

## 1. Hydraulic System: The First Three Days

### Symptom
The servo pushed the syringe plunger, but the neck barely moved. Water leaked steadily from the tubing connections onto the base. When it did move, it would rise halfway and stall.

### Root Cause (Three Separate Problems)

**Wrong tubing size.** The first build used 1/4" inner diameter tubing instead of the required 3/16" ID. The tubing fit loosely over the syringe Luer lock tips, so water bypassed the connection on every stroke. Fixed by ordering the correct 3/16" ID vinyl tubing and rebuilding the fluid path.

**Air bubbles in the line.** Even after the correct tubing was installed, the neck would stall mid-lift. Air pockets in the tube compressed under pressure instead of transmitting force. Fixed by slow-cycling the servo while tapping the line to coax bubbles upward, then fully priming the system before operation.

**Popsicle stick linkage geometry.** The connector between the servo horn and the syringe plunger was pushing at an angle instead of straight along the plunger axis. This wasted torque fighting the geometry. Fixed by repositioning the syringe mount and adjusting the linkage attachment point so the push was a straight line.

### Stress Test
After all three fixes, the system ran 40+ cycles over two days without a single failure.

---

## 2. PIR Sensor: Phantom Triggering

### Symptom
The sequence would start randomly with nobody in front of the sensor. Sometimes it fired twice in a row during calibration.

### Root Cause (Two Issues)

**Sensitivity potentiometer set too low.** The HC-SR501 has a small dial on the board. It was turned too far counterclockwise, making the sensor barely register heat signatures and occasionally misread electrical noise as a trigger. Turning the dial clockwise toward the max sensitivity mark resolved the phantom triggering almost immediately.

**60-second warm-up ignored.** The HC-SR501 behaves erratically during its first 60 seconds after power-on. We kept powering up and immediately testing. Once we made it standard practice to wait 60 seconds after power-on before any interaction, the behavior became completely reliable.

### Competition Protocol
Set at check-in: power on the system, start the 60-second timer, then proceed with setup while the sensor stabilizes.

---

## 3. DFPlayer Mini: No Audio

### Symptom
Code uploaded, connections checked, nothing played. The module appeared dead.

### Root Cause (Two Problems)

**Voltage divider built wrong.** The DFPlayer Mini RX pin expects 3.3V logic, but the Arduino outputs 5V. The fix requires a voltage divider: a 680Ω resistor from Arduino TX to the junction, then a 1KΩ resistor from the junction to ground, with the DFPlayer RX connected at the junction (outputs ~2.98V). The divider was initially wired with incorrect resistor values. Rebuilding it with 680Ω + 1KΩ fixed the communication immediately.

**Wrong file naming convention.** The DFPlayer requires audio files to be stored in a folder called `mp3` on the root of a FAT32-formatted SD card, with filenames starting with a four-digit number (e.g., `0001_harriet_narration.mp3`). The file was initially named without leading zeros.

### Fix Summary
- Rebuilt voltage divider: 680Ω (TX→junction) + 1KΩ (junction→GND)
- Renamed audio file to `0001_` prefix
- Verified card was FAT32 (Patriot 16GB)

---

## 4. Power System: Mid-Sequence Restarts

### Symptom
During full-sequence testing, the Arduino would reset mid-way — usually when the head servo and hydraulic servo fired simultaneously. Audio cut out, servos twitched, sequence restarted from the beginning.

### Root Cause
The servos were powered from the Arduino's 5V pin, which can source roughly 500mA. Multiple MG996R servos drawing current simultaneously pulled the rail voltage below the ATmega328P's brownout threshold, causing a reset.

### Fixes Applied
- Moved all servo power off the Arduino 5V pin and onto a dedicated 6V rail from a 4×AA battery pack (1.5V × 4 = 6V).
- Added a 1000µF 25V electrolytic capacitor across the servo power rail to act as a local charge reservoir during sudden current demand.
- Established a common ground between Arduino GND and the battery pack GND.

### Stress Test
After both changes, the full sequence ran 30 consecutive times with zero resets.

---

## Summary of All Fixes

| Problem | Actual Cause | Fix |
|---------|-------------|-----|
| Hydraulic leak | 1/4" tubing instead of 3/16" ID | Replaced with correct tubing |
| Hydraulic stall | Air bubbles in fluid line | Bled system by slow-cycling + tapping |
| Hydraulic inefficiency | Popsicle stick linkage at wrong angle | Realigned for straight-line push |
| Phantom PIR triggers | Sensitivity dial too low | Turned clockwise toward max |
| Phantom PIR triggers | No warm-up wait | Added 60s power-on delay |
| DFPlayer silent | Voltage divider resistor values wrong | Rebuilt with 680Ω + 1KΩ |
| DFPlayer silent | Missing leading zeros in filename | Renamed to 0001_ prefix |
| Arduino resetting | Servos on Arduino 5V pin (overcurrent) | Moved to 4×AA battery pack 6V rail |
| Arduino resetting | No transient buffer on servo rail | Added 1000µF capacitor |