# Changelog

All notable changes to "The North Star" animatronic repository are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html). Commit messages follow [Conventional Commits](https://www.conventionalcommits.org/).

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
