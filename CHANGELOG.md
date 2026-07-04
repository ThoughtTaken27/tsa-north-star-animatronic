# Changelog

All notable changes to "The North Star" animatronic repository are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html). Commit messages follow [Conventional Commits](https://www.conventionalcommits.org/).

## [v1.1] - 2026-07-04

### Fixed

- Corrected DFPlayer narration filename from `0001_harriet.mp3` to `0001.mp3` across README, schematic, postmortem, and code comments. The DFPlayer `0x12` command expects 4-digit-numbered files in the `/mp3` folder.
- Enhanced PIR sensor postmortem entry: documented the unlabeled pin identification process, correct potentiometer settings (sensitivity fully clockwise, delay fully counter-clockwise), and jumper cap position (H mode).
- Added macOS `dot_clean` failure to postmortem: hidden `._` resource fork files on the SD card crash the DFPlayer.

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
- 680 Ω / 1 kΩ voltage divider on the Arduino `D2` to DFPlayer RX; FAT32 microSD with narration at `/mp3/0001.mp3`.

### Known Limitations

- ASCII schematic only — no KiCad/Fritzing export yet.
- `docs/assets/` referenced in the media plan is not yet populated; final photos and demo clips are pending.
- No off-hardware unit tests for the FSM logic.
