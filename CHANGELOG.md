# Changelog

All notable changes to "The North Star" animatronic repository are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html). Commit messages follow [Conventional Commits](https://www.conventionalcommits.org/).

## [v1.4.1] - 2026-10-14

### Fixed

- **Soap description matched to the build record.** The build record says dish soap was used as a syringe/plunger lubricant and ruined two syringes; it does not say the soap was mixed into the hydraulic water. The postmortem, evidence summary, and v1.4 entry now say "used as a plunger lubricant" instead of "added to the water."

## [v1.4] - 2026-08-05

Full line-by-line audit of the repository against the complete build record (the March 28 project-transfer document plus the April 8-13 build/debug session log) and against the four build photographs. Every claim in every file was checked. The corrections below are the ones that were wrong. Where the source notes hedge, the docs now hedge with them instead of hardening a maybe into a fact.

### Fixed

- **Hydraulic fill procedure corrected.** The repo said the system was filled "by submerging the tubing and forcing water through both syringes" and bled "by cycling the plunger with the tubing end submerged." Neither is what happened, and "forcing water through both syringes" describes the exact mistake the procedure exists to avoid. Replaced with the real method: submerge one syringe and draw the plunger up until the barrel is bubble-free, attach the tubing to that syringe's nozzle only, push the plunger in slowly over a sink until water fills the tube as well, then attach the second empty syringe while that end is still wet. Submerging is involved — the syringe is drawn full under the surface — but there is no reservoir and the second syringe is never coupled underwater.
- **Stiction causality was backwards.** The postmortem said "the syringe's factory coating caused stiction after extended use." The opposite is true: the factory coating is what prevents stiction, and dish soap used as a plunger lubricant stripped it, ruining two syringes. Rewritten with the correct cause and the correct fix (clean water only, preserve the coating).
- **PIR failure symptom was wrong.** The postmortem described the HC-SR501 problem as false triggering. The build record shows the opposite: the sensor did not usefully trigger at all for roughly two days. Rewritten with the real symptom and the three real causes (unlabeled pinout, reversed sensitivity potentiometer on this board revision, jumper on L instead of H).
- **Damaged first sensor was omitted.** The postmortem credited "exhaustive testing" of pin combinations as the fix. Trying pin combinations is what took the first sensor out; the build notes record it as "likely damaged during wrong pin testing," and this entry keeps that hedge rather than upgrading it to a confirmed kill. The correct pinout came from the manufacturer's product image, and a fresh module from the 3-pack was swapped in.
- **Right/left arm convention stated explicitly.** "Right arm" now means the arm on the viewer's right as they face the exhibit, which is the syringe-driven pointing arm. The docs previously used "right-side" without ever defining the reference frame, which made the mechanical description ambiguous. The plain metal pin shoulder pivot is confirmed correct and unchanged; the pre-competition notes had floated a gutted SG90 body as the dead hinge instead, which is not what was built, and `docs/evidence_summary.md` now says so.
- **The second syringe was missing from the entire mechanical description.** `hardware/mechanical_assembly.md`, `docs/assembly_guide.md`, the schematic, the README system table, the README mermaid diagram, and `hardware/bom.md` ("1 visible in final build") all described a single syringe. Fluid power in this build is a closed two-syringe master/slave circuit — drive syringe on the base, tubing up the spine, output syringe at the shoulder — and the second syringe is visible in the reveal photo. This was the largest technical omission in the repository. Corrected everywhere, with a dedicated fluid-power section added to the schematic.
- **Invented dimensions removed from the schematic.** `5/16" wood dowel`, `~14" spine`, `4" PVC shoulders`, `~4" neck post`, and `3/4" plywood` were never recorded anywhere in the build record. The publishing guide explicitly forbids claiming measurements the repo cannot defend, so they are gone. What remains is the ~12x12 in base, the 6 in foam ball, and the competition's 15" x 3' x 4' resting envelope.
- **Firmware provenance claim corrected.** The README described `firmware/firmware.ino` as a "hand-reconstruction of the firmware read back off the competition Arduino." No flash read-back happened. The file is the final source from the April 10 development session, preserved verbatim, and is now described that way.
- **Serial baud rate ambiguity.** The README build instructions said to open Serial Monitor at 115200. That is correct for the modular FSM sketch and wrong for the competition firmware, which runs at 9600 and additionally needs the `DFRobotDFPlayerMini` library. Both are now stated.
- **v1.0-competition changelog entry corrected.** It listed the modular FSM firmware under the competition build's "Added" section, which contradicts that firmware's own header describing it as a post-competition rewrite.
- **Lantern servo mounting corrected** in `docs/engineering_notebook.md`, `docs/assembly_guide.md`, and the schematic. It is zip-tied to the end of the horizontal shoulder crossbar, per the photos, not mounted "on the left shoulder" or glued into a PVC elbow.
- **Servo rail voltage qualified.** The BOM and schematic stated a flat "6V servo rail." 6V is the alkaline nominal; the competition photo shows NiMH rechargeables installed, which is closer to 4.8V. Both are now noted so "6V" is not read as a measurement.
- **Unverifiable PIR delay figure removed** ("shortest output pulse, approximately 3 seconds"). The direction of the potentiometer is recorded; the resulting pulse length was never measured.

### Added

- **Five previously undocumented build failures and decisions** in `docs/postmortem_failure_log.md`: the macOS Arduino IDE library/permissions failure (`DFRobotDFPlayerMini.h: No such file or directory`) that ate time from the audio-debugging budget while being a toolchain problem, recorded honestly as "resolved by several fixes applied together" because no single root cause was isolated; the power-up servo jump and the `write()`-before-`attach()` fix, which is visible in the shipped firmware's own comments; the decision to mount the fluid power assembly on top of the base after the under-base idea ran out of clearance; the jaw movement scope cut and the resulting unallocated D10; and the narration/voice direction, recorded as direction given rather than as a claim about the final audio file. The hot glue plus zip tie mounting method moved into `hardware/mechanical_assembly.md` as build practice rather than being written up as a failure event, since the notes record it as a rule that was followed, not a mount that tore off.
- **Hydraulic servo angle history.** Push angles were found by testing, not calculation: 18 degrees verified good and shipped; a later trial at 15 was flagged as a grinding risk because it sits closer to the physical stop. Recorded in the postmortem, assembly guide, and schematic, along with the direction to move if grinding ever appeared (up, never down).
- **The April 9 DFPlayer recurrence is documented.** It failed again at the hotel after travel and a re-recorded audio file, was worked through a four-step checklist, and was working for the competition the next day. Which step was the actual fix was never written down, so the repo names the checklist and does not name a root cause.
- **DFPlayer graceful-degradation behavior** documented as a deliberate reliability decision rather than an incidental code branch.
- **Dated build timeline** in `docs/engineering_notebook.md` anchored to receipts and the competition record.
- **Photo-verified build details section** in `docs/evidence_summary.md`, listing what the four photographs independently confirm and flagging where they override the pre-competition planning notes.
- **1849 and the age-27 depiction** in `docs/historical_context.md`, including why the familiar elderly-Tubman image was deliberately avoided and how that drove the voice recording decisions.
- **Naming convention note** clarifying that the firmware's `leftArmServo` / `hydraulicServo` labels follow the team's build convention.

### Changed

- Code contribution attribution in `docs/engineering_notebook.md` now states that the firmware was written with help from a friend, matching the build record, rather than implying it was written solo.

### Added (second pass)

- **Scale-of-effort summary** at the top of `docs/postmortem_failure_log.md` and in the README: 23 logged traps, split into 15 diagnosed faults, 8 conceptual errors caught early, and 2 competition-window incidents, with the two that cost hardware named.
- Fixed a section numbering gap in the failure log (it skipped 12).

### Explicitly Not Claimed

A short list of things the build record does not settle, kept here so future edits do not quietly harden them into facts:

- Whether the narration file that played at competition was voice-changed or plain. A processed file is recorded as being on the card on April 9; the direction given was to use an unprocessed female voice. The log states the direction and stops there.
- What position the PIR trigger-mode jumper shipped in. H is recorded as the required setting and is what it ran on; "it was found on L" is not in the notes.
- Which of the four checklist steps actually fixed the April 9 DFPlayer failure.
- Which of the four fixes actually resolved the macOS Arduino IDE library error.
- Whether the first PIR sensor was genuinely dead. The notes say "likely damaged."
- Any frame dimension beyond the base footprint and the 6 in foam ball.

## [v1.3] - 2026-07-10

### Fixed

- **Postmortem DFPlayer pin reference corrected**: voltage divider was listed as "Arduino D2 to DFPlayer RX" — D2 is Arduino RX (receives from DFPlayer TX). The divider is on D3 (Arduino TX → DFPlayer RX). Updated `docs/postmortem_failure_log.md` and `CHANGELOG.md` v1.0 reliability fixes section.
- **Fabricated `dot_clean` claim removed from postmortem**: the `dot_clean` / macOS resource fork claim in `docs/postmortem_failure_log.md` was not supported by the build record. Replaced with the actual DFPlayer failure causes: micro SD card not fully seated in the module slot (causing intermittent connection failures under servo vibration) and loose breadboard contact quality. Updated CHANGELOG v1.1 entry accordingly.
- **Stale filename comment in `src/StateEngine.cpp`**: comment still referenced `/mp3/0001_harriet.mp3` instead of `/mp3/0001.mp3`. The CHANGELOG v1.1 claimed to have corrected this "across README, schematic, postmortem, and code comments" but the StateEngine.cpp comment was missed.
- **Missing vinyl tubing in BOM and evidence summary**: `hardware/bom.md` and `docs/evidence_summary.md` did not list the 3/16 in ID clear vinyl tubing (10 ft roll) used for the hydraulic fluid transfer between syringes. Added as a separate line item.
- **Servo angle tables clarified**: `hardware/schematics/system_schematic_ascii.txt` and `docs/assembly_guide.md` listed servo home positions without distinguishing between the modular FSM version and the competition firmware values. Now both versions' values are shown side by side with a note explaining the difference.
- **CHANGELOG v1.1 PIR potentiometer direction corrected**: the v1.1 entry said "sensitivity fully clockwise" — on the HiLetgo HC-SR501 revision used, maximum sensitivity is fully counter-clockwise. The postmortem was already corrected in v1.2, but the v1.1 changelog entry itself still contained the wrong direction.
- **CHANGELOG v1.2 microSD capacity entry updated**: the v1.2 changelog claimed microSD was "corrected from 8 GB to Patriot LX 16 GB", but a later commit (`b746122`) reverted it back to 8 GB because the pack listing showed 16 GB but the actual cards were 8 GB each. Updated the changelog to reflect the final state.
- **Photo-verified corrections**: cross-checked build photos against repo docs and fixed three discrepancies: (1) the syringe drive linkage was described as "popsicle stick" / "popstick" / "wood linkage" in the schematic, assembly guide, BOM, and postmortem — photos confirm it is a round wooden dowel, not a popsicle stick. All references updated to "wooden dowel linkage". (2) The plywood base was described without paint or feet — photos show it is painted white with four short wooden dowel feet. Updated `mechanical_assembly.md`, `system_schematic_ascii.txt`, and `hardware/bom.md`. (3) Confirmed the microcontroller is Arduino Uno R3 (blue PCB) as documented — no Nano was used in the competition build.

### Added

- **Build photos**: added 4 verified build photos to `docs/assets/` — `exhibit.jpg` (completed exhibit with fabric shell), `wiring.jpg` (electronics layout on white-painted base), `syringe_linkage.jpg` (MG996R servo driving 60 mL syringe through wooden dowel linkage), and `reveal.jpg` (exposed PVC skeleton with both arms and syringes). Updated README with an image table and publishing guide with asset status. A short full-sequence demo clip (`demo_hook.gif`) is still needed.
- **Firmware file renamed**: `firmware/board_firmware_recovered.ino` → `firmware/firmware.ino` to satisfy the Arduino CLI sketch naming convention (`.ino` file must match parent folder name). Updated all references in README, `tsa-north-star-animatronic.ino`, `docs/assembly_guide.md`, `scripts/verify_files.py`, and the CI workflow. This fixes the "Compile Arduino Firmware" CI badge failure.

## [v1.2] - 2026-07-10

### Fixed

- **Critical: board_firmware_recovered.ino replaced with actual competition code.** The previous version claimed to be a flash-dump reconstruction but was inaccurate — it used raw DFPlayer packets instead of the DFRobotDFPlayerMini library, had wrong servo angles (head 85/120 vs 60/90, arm 90 vs 18), lacked the millis()-clocked hydraulic delay, and did not implement the North Star beacon behavior. The new version is the blocking firmware that actually ran at competition.
- **Critical: DFPlayer D2/D3 pin labels were swapped** in `hardware/bom.md`, `hardware/schematics/system_schematic_ascii.txt`, and `tsa-north-star-animatronic.ino`. The code uses `SoftwareSerial(2, 3)` which means RX=2, TX=3. D2 is Arduino RX (from DFPlayer TX direct), D3 is Arduino TX (to DFPlayer RX through divider). All three files now match the actual wiring.
- Corrected PIR sensitivity potentiometer direction in `docs/postmortem_failure_log.md`: fully counter-clockwise (not clockwise) for maximum sensitivity on the HiLetgo HC-SR501 revision used.
- Reviewed microSD card capacity: the Amazon listing showed "16 GB" but the actual cards in the pack were 8 GB each. The BOM and evidence summary were updated to reflect the real 8 GB capacity, then corrected back to 8 GB after a temporary 16 GB edit.
- Corrected `NARRATION_DURATION` in `src/StateEngine.h` from 75000ms to 33000ms (33 seconds, matching the actual narration file).
- Corrected `GESTURE_TRIGGER_MS` in `src/StateEngine.h` from 30000ms to 18000ms (18 seconds after audio start, matching the actual competition timing).

### Added

- README firmware version comparison section documenting the difference between the modular FSM rewrite (`tsa-north-star-animatronic.ino`) and the actual blocking competition code (`board_firmware_recovered.ino`).
- Updated README behavior description to match the actual competition sequence: North Star beacon between rounds, 18-second hydraulic delay, lights-reset at trigger, outro sequence.

## [v1.1] - 2026-07-04

### Fixed

- Corrected DFPlayer narration filename from `0001_harriet.mp3` to `0001.mp3` across README, schematic, postmortem, and code comments. The DFPlayer `0x12` command expects 4-digit-numbered files in the `/mp3` folder.
- Enhanced PIR sensor postmortem entry: documented the unlabeled pin identification process, correct potentiometer settings (sensitivity fully counter-clockwise for maximum sensitivity on the HiLetgo HC-SR501 revision used, delay fully counter-clockwise for shortest pulse), and jumper cap position (H mode).
- Added DFPlayer reliability note to postmortem: the DFPlayer Mini was sensitive to breadboard contact quality and micro SD card seating. Intermittent "DFPlayer not found" errors were caused by the SD card not being fully seated and loose breadboard connections, not by macOS resource fork files.

### Added

- Documented the right-arm passive pivot: a plain metal pin through a drilled hole at the shoulder, not a powered servo. Updated mechanical assembly guide, schematic, and assembly guide.

### Changed

- Merged stale `[Unreleased]` section into this versioned entry. CI badge, CONTRIBUTING.md, and CHANGELOG.md were already committed in the v1.0 PR.
- Added `CHANGELOG.md` and `CONTRIBUTING.md` to the `verify_files.py` link integrity check.

## [v1.0-competition] - 2026-04-10

Competition build shipped to the 2026 Tennessee TSA State Leadership Conference — **1st place, 127 / 130**. Tagged at the shipped commit as `v1.0-competition` (the competition-evaluation date, not the date of the repository's git history).

### Added

*(Corrected in v1.4: the modular FSM firmware listed below is a post-competition rewrite for portfolio clarity, not part of the shipped competition build. The firmware that actually ran at the conference is `firmware/firmware.ino`. The entries below are kept because this is the release where the repository itself was created.)*

- Non-blocking finite state machine firmware for an Arduino Uno-compatible ATmega328P board (`tsa-north-star-animatronic.ino` and `src/`).
  - `StateEngine` — seven-state FSM (sensor warm-up, idle, triggered, speaking, gesture, return-to-home, rest cooldown) coordinated with `millis()`.
  - `Actuators` — ramped servo wrapper with hardware-safe angle limits.
  - `Sensors` — HC-SR501 PIR motion sensor with 150 ms temporal debounce.
  - `AudioController` — DFPlayer Mini serial packet interface.
- Hardware documentation: bill of materials and pin map ([`hardware/bom.md`](./hardware/bom.md)), mechanical assembly notes ([`hardware/mechanical_assembly.md`](./hardware/mechanical_assembly.md)), ASCII wiring diagram ([`hardware/schematics/system_schematic_ascii.txt`](./hardware/schematics/system_schematic_ascii.txt)).
- Engineering documentation: assembly guide, postmortem failure log, historical context, engineering notebook, evidence summary, and publishing guide (see [`docs/`](./docs/)).
- `scripts/verify_files.py` — programmatic repository path, file-presence, and markdown link-integrity verification.
- GitHub Actions workflow ([`.github/workflows/compile.yml`](./.github/workflows/compile.yml)) compiling the sketch with `arduino-cli` and running the verification script on every push and pull request.
- `.clang-format` (Google base, 4-space indent, 100-column limit).
- MIT open-source license.

### Reliability Fixes Applied During the Build

These are documented in detail in [`docs/postmortem_failure_log.md`](./docs/postmortem_failure_log.md):

- Separated servo power rail (switched 4xAA) from Arduino logic (9V) with a shared ground; added a 1000 µF capacitor across the servo rail.
- 60-second PIR warm-up lock and post-show cooldown to suppress false triggers.
- Repositioned the syringe linkage and reduced software travel limits so the MG996R stayed inside its reliable mechanical range.
- 680 ohm / 1 kohm voltage divider on the Arduino `D3` (TX) to DFPlayer RX; FAT32 microSD with narration at `/mp3/0001.mp3`.

### Known Limitations

- ASCII schematic only — no KiCad/Fritzing export yet.
- `docs/assets/` referenced in the media plan is not yet populated; final photos and demo clips are pending.
- No off-hardware unit tests for the FSM logic.
