# The North Star - Harriet Tubman Animatronic Exhibit

[![Competition](https://img.shields.io/badge/Competition-Tennessee%20TSA%20State%202026-gold.svg?style=flat-square)](https://github.com/Parthkkk/tsa-north-star-animatronic)
[![Platform](https://img.shields.io/badge/Platform-Arduino%20Uno-blue.svg?style=flat-square)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B%20%2F%20Embedded-brightgreen.svg?style=flat-square)](https://isocpp.org/)

"The North Star" is a portable Arduino animatronic exhibit built for the 2026 Tennessee TSA Animatronics event. The figure represents Harriet Tubman as a children's museum-style exhibit: when a viewer approaches, a PIR sensor starts the narration, the head turns, the lantern lights, a fluid-powered arm rises toward the North Star, and the sequence resets for the next viewer.

The project placed **1st at the Tennessee TSA State Championship**. This repository is a cleaned technical record of the firmware, wiring, build notes, and postmortem. Claims here are kept to what is supported by the project notes, exported Claude build history, and the current source code.

## System Summary

| Area | Final Build |
| :--- | :--- |
| Controller | Arduino Uno-compatible ATmega328P board |
| Trigger | HC-SR501 PIR motion sensor |
| Audio | DFPlayer Mini with microSD narration file |
| Motion | MG996R head turn servo, MG996R syringe-drive servo, SG90 lantern arm servo |
| Lighting | Warm white lantern LED, orange/amber North Star LED |
| Fluid Power | Two 60 mL syringes connected by 3/16 in vinyl tubing with blue-tinted water |
| Power | 9V battery to Arduino barrel jack, 4xAA battery pack for servo rail, shared ground |
| Reliability Fixes | Servo rail capacitor, DFPlayer voltage divider, PIR warm-up protocol, tubing and linkage corrections |

## Behavior

1. The Arduino waits through a 60-second PIR warm-up window after power-on.
2. Motion on the PIR sensor starts the sequence.
3. The DFPlayer plays `/mp3/0001_harriet.mp3`.
4. The lantern LED turns on and the head servo turns toward the viewer.
5. The hydraulic servo pushes the controller syringe, raising the arm through the water-filled line.
6. The North Star LED turns on during the pointing gesture.
7. The servos return home, audio stops, and the system enters a short cooldown.

The firmware avoids blocking timing during the show loop. Servo movement, LEDs, sensor checks, and state transitions are coordinated with `millis()` through a finite state machine.

## Architecture

```text
                         +----------------------+
                         |  Arduino Uno / AVR   |
                         +----------+-----------+
                                    |
             +----------------------+----------------------+
             |                      |                      |
      PIR sensor D7          DFPlayer D2/D3          LEDs D4/D5
             |                      |                      |
      motion trigger       narration playback      North Star + lantern
                                    |
             +----------------------+----------------------+
             |                      |                      |
       Head servo D9       Hydraulic servo D6      Lantern servo D11
             |                      |                      |
       turns head          pushes syringe line      raises lantern arm
```

## Repository Map

- [`tsa-north-star-animatronic.ino`](./tsa-north-star-animatronic.ino) - Arduino entry point and pin assignments.
- [`src/StateEngine.cpp`](./src/StateEngine.cpp) - Non-blocking sequence state machine.
- [`src/Actuators.cpp`](./src/Actuators.cpp) - Ramped servo wrapper with safe angle limits.
- [`src/Sensors.cpp`](./src/Sensors.cpp) - PIR debounce handling.
- [`src/AudioController.cpp`](./src/AudioController.cpp) - DFPlayer serial packet interface.
- [`hardware/bom.md`](./hardware/bom.md) - Bill of materials and pin map.
- [`hardware/mechanical_assembly.md`](./hardware/mechanical_assembly.md) - Physical frame and linkage notes.
- [`hardware/schematics/system_schematic_ascii.txt`](./hardware/schematics/system_schematic_ascii.txt) - Text wiring diagram.
- [`docs/assembly_guide.md`](./docs/assembly_guide.md) - Assembly and calibration guide.
- [`docs/postmortem_failure_log.md`](./docs/postmortem_failure_log.md) - Real build failures and fixes.
- [`docs/historical_context.md`](./docs/historical_context.md) - Historical and presentation context.
- [`docs/engineering_notebook.md`](./docs/engineering_notebook.md) - Timeline and team roles.

## Build and Upload

1. Open [`tsa-north-star-animatronic.ino`](./tsa-north-star-animatronic.ino) in the Arduino IDE.
2. Select **Arduino Uno** as the board.
3. Install the standard `Servo` library if it is not already installed.
4. Format the microSD card as FAT32.
5. Create a folder named `mp3` on the card.
6. Save the narration as `0001_harriet.mp3` inside that folder.
7. Upload the sketch.
8. Open Serial Monitor at `115200` baud for state transition logs.

## Evidence Standard

Some early planning notes and generated drafts described parts that were not supported by the final build evidence, such as machined Delrin plungers, oscilloscope voltage captures, a custom neck-lift cylinder, and exact current measurements. Those details are intentionally not used here. The public repo should read like a strong high-school engineering project, not a lab report with invented precision.
