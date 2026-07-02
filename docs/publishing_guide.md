# GitHub Publishing Guide - "The North Star"

This repository should read as a clean engineering portfolio, not as a dramatized competition essay. Keep claims specific, verifiable, and consistent with the code.

## Before Publishing

Run the local verification script:

```bash
python3 scripts/verify_files.py
```

Check these manually:

- README links work.
- Pin map matches the `.ino` file.
- The BOM matches the actual parts used.
- Any media you add shows the real build, not a generated mockup.
- The repo does not claim measurements or parts you cannot defend.

## GitHub Setup

Recommended repository metadata:

- **Name:** `tsa-north-star-animatronic`
- **Description:** `Tennessee TSA state-winning Arduino animatronic exhibit with PIR trigger, DFPlayer audio, LEDs, servo motion, and a syringe-driven arm.`
- **Topics:** `arduino`, `embedded-systems`, `robotics`, `animatronics`, `servo`, `dfplayer`, `hardware-portfolio`, `tsa`

## Suggested Visual Assets

Add real media if available:

- `docs/assets/demo_hook.gif` - 10-15 second full sequence.
- `docs/assets/wiring.jpg` - clear electronics photo.
- `docs/assets/syringe_linkage.jpg` - syringe mechanism photo.
- `docs/assets/reveal.jpg` - removable shell / internal skeleton.

Do not add these paths to the README until the files exist.

## Application Copy

Short version:

> Built a 1st-place Tennessee TSA animatronic exhibit with Arduino control, PIR triggering, DFPlayer audio, LED lighting, servo motion, and a syringe-driven arm.

More technical version:

> Led systems integration for a 3-person TSA animatronics team, building the Arduino control stack, wiring, DFPlayer audio, servo sequencing, and reliability fixes for a battery-powered Harriet Tubman museum exhibit.

## Claim Rules

- Say "battery-powered" only when describing the competition presentation setup.
- Say "syringe-driven linkage"; avoid making the arm mechanism sound more complex than it is.
- Do not claim oscilloscope measurements unless there is a saved trace or photo.
- Do not claim machined parts, custom seals, or precision fabrication unless there is evidence.
- Keep judge feedback phrased as feedback, not as an official written score unless you have the score sheet.
