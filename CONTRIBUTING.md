# Contributing to "The North Star"

This repository documents a completed competition build (1st place, Tennessee TSA State 2026). It is currently a solo project, but issues and pull requests are welcome — especially reliability fixes, documentation corrections, and improvements to the verification/CI tooling.

## Development Setup

1. Open `tsa-north-star-animatronic.ino` in the Arduino IDE (or VS Code with the Arduino extension).
2. Select **Arduino Uno** as the target board.
3. Install the standard `Servo` library if it is not already available.
4. See [`docs/assembly_guide.md`](./docs/assembly_guide.md) for hardware setup and calibration.

## Before Opening a Pull Request

1. Run the integrity script and confirm it passes:

   ```bash
   python3 scripts/verify_files.py
   ```

2. If your change touches firmware, confirm it compiles. Locally with `arduino-cli`:

   ```bash
   arduino-cli core install arduino:avr
   arduino-cli lib install Servo
   arduino-cli compile --fqbn arduino:avr:uno tsa-north-star-animatronic.ino
   ```

   The GitHub Actions workflow runs the same compile step on every push, so CI will catch anything missed locally.

3. Make sure any new markdown links resolve. The `verify_files.py` script checks link integrity, but it does not catch links inside code fences or external URLs.

## Commit Convention

This repository uses [Conventional Commits](https://www.conventionalcommits.org/). Prefix commit messages with one of:

- `feat:` — new firmware behavior or hardware capability
- `fix:` — a bug fix
- `docs:` — documentation only
- `style:` — formatting, `.clang-format`, no logic change
- `refactor:` — code restructuring with no behavior change
- `test:` — additions or changes to the verification/CI scripts
- `ci:` — GitHub Actions workflow changes
- `chore:` — maintenance (dependencies, configs)

Keep the subject line under 72 characters. Reference the affected subsystem in the body when useful (e.g., `Sensors`, `Actuators`, `StateEngine`, `AudioController`).

## Claim Accuracy

When editing documentation, keep claims consistent with the actual build and the evidence in [`docs/evidence_summary.md`](./docs/evidence_summary.md). Do not introduce claims about measurements, machined parts, or precision fabrication that the repository cannot defend. See [`docs/publishing_guide.md`](./docs/publishing_guide.md) for the full claim rules.
