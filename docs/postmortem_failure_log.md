# Engineering Failure Log - "The North Star"

This postmortem records the failures that actually shaped the final build: power stability, sensor reliability, audio playback, and the mechanical alignment of the exposed servo/syringe system.

**Every item below was resolved before the competition.** The exhibit ran its full sequence correctly at the Tennessee TSA State Leadership Conference on April 10, 2026, self-contained on battery power with no laptop attached. This log exists because the path there is more useful than the outcome, not because anything was still broken at the end.

Where the build notes hedge, this log hedges too. Items marked as "likely" or "flagged as a risk" are recorded that way on purpose.

## 1. Servo Power Resets

**Symptom:** The Arduino would reset or behave unpredictably when multiple servos moved.

**Cause:** The servos could pull enough current during movement to disturb the control electronics when power was not separated cleanly.

**Fix:**

- Powered servos from a separate switched 4xAA battery pack.
- Kept Arduino logic on its own 9V input.
- Tied all grounds together so signal references stayed consistent.
- Added a 1000 uF capacitor across the servo rail to reduce short voltage dips.

## 2. PIR Sensor Would Not Trigger

**Symptom:** For roughly two days the HC-SR501 did not usefully trigger the sequence. The wiring looked correct and the detection code was correct, so the failure appeared to be software when it was not.

**Cause:** Three separate problems, none of them visible from the code side.

1. The HiLetgo HC-SR501 modules used here have no printed pin labels on the component side. The pinout had to be established before anything else could be trusted.
2. The sensitivity potentiometer on this board revision behaves opposite to the direction described in most general HC-SR501 guides. Turning it the way the common guides call "maximum" was actually reducing sensitivity.
3. Trigger mode. The HC-SR501 selects between non-repeatable (L) and repeatable (H) with a jumper across a three-pin header. In L the sensor fires once and then locks out until its delay timer expires, which is the wrong behaviour for a visitor standing in front of an exhibit. The build notes record H as the required setting. They do not record what position it shipped in, so this log does not claim the jumper was found wrong — only that H is what the exhibit needs and H is what it ran on.

**What went wrong during diagnosis:** the first attempt at establishing the pinout was to try pin combinations by swapping the power and ground leads. The first sensor stopped working during that process and was set aside as likely damaged; the build notes record it as "likely damaged during wrong pin testing" rather than as a confirmed kill. The correct pinout was ultimately read off the manufacturer's product image rather than derived by trial and error. The sensors came as a 3-pack, so a fresh module was swapped in and the build continued without delay. The practical lesson stands regardless of whether that first module was actually dead: do not brute-force an unlabeled sensor's power pins when the manufacturer's own listing photo shows the order.

**Fix:**

- Established the correct pin order from the manufacturer's product photo: with the Fresnel dome facing you and the pins pointing down, VCC / OUT / GND left to right.
- Moved to a fresh module from the same 3-pack. The third module was kept as a spare and was never needed.
- Turned the sensitivity potentiometer fully counter-clockwise, which is maximum sensitivity on this board revision.
- Turned the time-delay potentiometer fully counter-clockwise for the shortest output pulse.
- Moved the on-board jumper cap to the H position (repeatable trigger mode).
- Added a 60-second startup warm-up lock in the firmware so the sensor can settle on a background infrared profile before triggers are accepted.
- Held the sequence until the PIR output returns LOW before re-arming, so one visitor cannot stack multiple runs.

**Note on the potentiometer direction:** this is a claim about the specific HiLetgo units in this build, established by testing them. It is not a general claim about every HC-SR501 on the market. Board revisions differ, which is exactly what made this take two days.

## 3. Syringe Linkage Binding

**Symptom:** The right arm (viewer's right) stalled, moved weakly, or pushed sideways instead of producing a clean gesture.

**Cause:** The syringe plunger and wooden dowel linkage were sensitive to angle. When the servo horn pushed off-axis, the mechanism wasted torque and the plunger resisted motion. Separately, the servo could be commanded past the mechanism's physical end stop. A hobby servo that cannot reach its commanded angle does not give up — it keeps applying torque against the stop indefinitely, which produces continuous audible grinding and risks stripping the gears or tearing the mount loose.

**Fix:**

- Repositioned the syringe body and support point.
- Adjusted the MG996R servo horn and short wooden dowel linkage so the push is as close to axial as the geometry allows.
- Added enough pivot freedom for the arm to move through its arc without forcing the syringe sideways.
- Mapped the usable syringe stroke to a safe servo range and stopped commanding outside it. The drive servo rests at 70 degrees. Push angles were found by testing: 18 degrees was verified good, and a later attempt at 15 degrees was flagged as a grinding risk because it pushes closer to the mechanism's physical stop. The competition firmware shipped with 18, and its inline comment keeps 19, 20, 21 as the direction to move if grinding ever appeared. Lower is toward the wall; higher is away from it.
- Accepted a limited stroke on purpose. The servo reliably produces roughly 2 cm of plunger travel. That was enough for a visibly clear gesture, and a repeatable small movement was judged more valuable than an ambitious one that failed intermittently.

## 4. Hydraulic Fluid System Issues

**Symptom:** The right arm moved inconsistently — sometimes strong, sometimes weak or delayed for no visible mechanical reason.

**Cause:** Two independent problems that looked like one intermittent problem.

1. **Trapped air.** Air inside the vinyl tubing acts as a spring. It compresses under pressure and absorbs part of the drive servo's stroke before the output syringe extends. Water is used precisely because it is effectively incompressible (bulk modulus ~2.2 GPa); any air pocket reintroduces compressibility and softens the force transfer unpredictably. Connecting both syringes and then filling guarantees trapped air, because the air in the second syringe has no exit path.
2. **Stiction from dish soap.** Dish soap was added to the water early in development on the assumption that it would lubricate the plungers. It did the opposite: it stripped the factory coating from the rubber seals, leaving static friction much higher than kinetic friction. The plunger would resist starting its stroke and then break away suddenly, so the arm motion varied cycle to cycle even when the servo swept identically. Two syringes were ruined this way before the cause was identified.

**Fix:**

- Used only clean water. No soap, no oil, no additives. Preserving the factory coating on the seals is the point.
- Changed the fill order to bleed air out instead of sealing it in:
  1. Submerge one syringe in water and draw the plunger up until the barrel is completely full with no bubbles in it.
  2. Attach the tubing to that syringe's nozzle. Leave the other end of the tube open.
  3. Standing over a sink, push the plunger in slowly until the water has completely occupied the tube as well.
  4. Attach the second, empty syringe to the still-wet open end.

  The order is the whole point. Drawing the water in under the surface is what keeps air out of the barrel, and pushing it through the open tube is what displaces the air out of the tube instead of trapping it. Connecting both syringes first and filling afterwards seals air into the second syringe with nowhere to go.
- Replaced the two soap-damaged syringes. The replacements were noticeably smoother, which confirmed the coating was the variable.
- Stored the syringes with the plunger left partway inside rather than fully removed, so the rubber seal does not dry out between sessions.
- Slowed the drive servo sweep in firmware (`hydraulicSpeed = 35` ms per degree versus 20 for the head and lantern arm) to give the fluid column time to transfer instead of shock-loading it.

## 5. Exposed Wiring Reliability

**Symptom:** Wires and servo leads could shift during testing, transport, or the removable-shell reveal.

**Cause:** The electronics were intentionally visible on the plywood base, which made the project easier to inspect but also exposed the wiring to bumps and pulls.

**Fix:**

- Routed wires along the PVC spine and base.
- Used zip ties to secure loose runs.
- Kept the Arduino, breadboard, DFPlayer, speaker, batteries, and PIR sensor accessible for inspection and troubleshooting.

## 6. DFPlayer Mini Wiring and SD Card Setup

**Symptom:** The DFPlayer failed to play narration during early tests.

**Causes:**

- The DFPlayer RX line needed a safer logic-level input from the Arduino TX pin.
- The SD card and file naming had to match the DFPlayer command being used.

**Fix:**

- Used a 680 ohm / 1k ohm voltage divider on Arduino `D3` (TX) to DFPlayer RX to step the 5V Arduino signal down to a safe level for the DFPlayer's 3.3V input.
- Formatted the microSD card as FAT32.
- Put the narration in `/mp3/0001.mp3`.
- Reseated the micro SD card fully into the DFPlayer slot (it was not fully inserted, causing intermittent connection failures under vibration from servo movement).
- Improved breadboard contact quality by pressing the DFPlayer module and all connecting wires firmly into the breadboard.
- Updated the firmware to use the DFPlayer command for numbered files in the `/mp3` folder.
- Added a presence check at startup so a missing module degrades gracefully instead of taking the show down. If `myDFPlayer.begin()` fails, `audioReady` stays false, every audio call is skipped, and the lights, head, arms, and hydraulic gesture still run on the same timeline. This mattered: the module was not reliably trustworthy going into the competition.

**Recurrence the night before competition:** the DFPlayer stopped working again on the evening of April 9, at the hotel after travel, immediately after a re-recorded narration file was loaded onto the card. It was worked through in this order: SD card seating first, then the exact `/mp3/0001.mp3` filename (an exported file with any other name is a silent failure and an audio editor will not name it for you), then breadboard connections, then the Serial Monitor to distinguish "DFPlayer ready" from "DFPlayer not found." It was working for the competition the next day. Which step in that list was the actual fix was not written down, so this entry does not name one.

## 7. Arduino IDE Could Not Find the DFPlayer Library (macOS)

**Symptom:** `DFRobotDFPlayerMini.h: No such file or directory` at compile time, on a Mac, with the library apparently installed.

**Cause:** The build notes list three candidate causes rather than one confirmed root cause, because several fixes were applied together and it started working.

- A leftover library folder in the Arduino libraries directory conflicting with a clean install.
- The sketch living in the IDE's unsaved temporary location rather than a real folder.
- The Arduino IDE not having macOS Files and Folders permission for Documents.

**Fix (applied together):**

- Deleted the suspect library folder manually via Terminal rather than through the IDE's library manager.
- Reinstalled `DFRobotDFPlayerMini` clean.
- Saved the sketch to a real folder instead of leaving it unsaved.
- Granted the Arduino IDE access to Documents under Privacy & Security > Files and Folders.

**Why it is in this log:** it looked like an audio problem and it ate time from the audio debugging budget, but it was a toolchain and OS-permissions problem. Misreading which layer a failure lives in was the recurring cost on this build. It is recorded honestly as "resolved by a combination of fixes," not as a clean single-cause diagnosis.

## 8. Servo Jump on Power-Up

**Symptom:** Servos swing to an arbitrary position the moment the board powers on, before the sequence code settles. On the syringe drive this means slamming the plunger.

**Cause:** `Servo.attach()` starts driving the output before any target angle has been written, so the servo runs to whatever the library's default pulse width corresponds to.

**Fix:** Write the intended home angle *before* calling `attach()` on every servo. This is visible in the shipped firmware, where `setup()` reads `headServo.write(headAway); headServo.attach(9);` in that order and not the reverse, with the inline comment "Set positions BEFORE attach to prevent startup jump." All three servos are initialised this way.

## 9. Hydraulics Moved to the Top of the Base

**Situation:** The initial idea was to fit the syringe assembly underneath the plywood base, in the gap created by its short dowel feet. That gap turned out to be too small to work in, and anything mounted under there would have been unreachable and invisible.

**Decision:** The whole fluid power assembly went on top of the base instead. This solved the clearance problem and produced two benefits that were not the original motivation: the mechanism became directly inspectable by judges during the shell reveal, and debugging it no longer meant getting under the exhibit.

## 10. Scope Cut: Jaw Movement Dropped

**Decision, not a failure, but it belongs in the record.** A fourth movement — an articulated jaw — was planned and cut. The competition requires a minimum of three movements. Three movements that ran reliably every time were worth more than four with one that was unfinished or intermittent. Digital pin 10 was left unallocated as a result and is unused in both firmware versions.

## 11. Narration Audio: Rejected the Voice Changer

**Problem:** The narration is Harriet Tubman speaking to a child. The obvious shortcuts were a male teammate's voice, or a processed voice through a video-editor voice changer.

**Reasoning:** Output is a 3 W, 8 ohm speaker in a noisy convention hall. Processing artifacts stack on top of a small speaker's own losses and reduce intelligibility, which costs more than any character gain. A fake elderly voice would also have been historically wrong — the exhibit depicts Tubman around 1849, when she was roughly 27.

**Direction given:** find a real female voice rather than processing a male one, record it plain, slow and quiet, in a small soft-furnished space to cut room echo, and export it as `0001.mp3` into the `/mp3` folder on the card.

**What the record actually shows:** the narration was re-recorded and re-exported at least once, and the build log notes that a voice-changer-processed file was on the card as of April 9. Whether the file that played at competition was processed or plain is not recorded, so this log does not claim either. The reasoning above is why processing was argued against; it is not a claim about the final file.

Independently verifiable: the show timeline is built on `audioLengthSeconds = 33`, so the narration the firmware was tuned against is 33 seconds long.

## 13. Competition-Day Backdrop Recovery

**Event:** During setup, the team realized the painted black star backdrop had been left in the nearby hotel room.

**Response:** One teammate retrieved the backdrop while the others continued setup, powered the electronics, and let the PIR warm-up period run.

**Outcome:** The exhibit was ready within the setup window. Judge feedback highlighted that the project was self-contained and did not need to remain plugged into a laptop during the presentation.

**Deliberately not claimed:** no stopwatch numbers are given here. The round-trip time and the margin at the end of the setup window were not measured, and inventing them would be the kind of fabricated precision this repository is trying to avoid. The 60-second PIR warm-up had to elapse regardless, which is the reason the parallel plan worked.
