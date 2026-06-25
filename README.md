# "The North Star" — Harriet Tubman Animatronic Bust

[![Badge: Competition](https://img.shields.io/badge/Competition-TSA%20Tennessee%20State%20Championship-gold.svg?style=flat-square)](https://github.com/Parthkkk/tsa-north-star-animatronic)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino%20Uno-blue.svg?style=flat-square)](https://www.arduino.cc/)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B%20%2F%20Embedded-brightgreen.svg?style=flat-square)](https://isocpp.org/)

"The North Star" is an interactive animatronic Harriet Tubman bust built for the Tennessee TSA State Championship (2026). The system uses an Arduino Uno, servo-driven syringe hydraulics for neck tilt, and a non-blocking finite state machine.

---

## Technical Overview

| Metric | Specification |
| :--- | :--- |
| **Competition** | TSA Tennessee State Championship (May 2026) |
| **Microcontroller** | ATmega328P (Arduino Uno R3) |
| **Actuators** | 3x TowerPro MG996R, 1x SG90 Micro Servo |
| **Neck Tilt** | Master-slave syringe hydraulics (60ml syringes, 3/16" PVC tubing) |
| **Audio** | DFPlayer Mini + 8Ω 3W speaker (voltage divider on RX line) |
| **Sensor** | HC-SR501 PIR (sensitivity dial adjusted, 60s warm-up required) |
| **Servo Power** | 4×AA battery pack (6V) with 1000µF capacitor |
| **Arduino Power** | USB (laptop / phone charger / USB power bank) |

---

## System Architecture

```text
  +────────────────────+          +──────────────────────────+
  │ ARDUINO UNO (USB)  │          │  4×AA BATTERY PACK (6V)  │
  │ 5V from USB port   │          │  (servo power only)      │
  +────┬───┬───┬───┬───+          +────────────┬─────────────+
       │   │   │   │                            │
       │   │   │   │    (PWM pins)              │
       │   │   │   ├────────────────────────────┼────┐
       │   │   │   │                            │    │
       │   │   │   ▼                   +────────┴──┐ │
       │   │   │   [MG996R Servos] ───>│ Common GND ├─┘
       │   │   │   (Yaw/Pitch/Jaw)     +───────────+
       │   │   │
       │   │   └────(D12)──> SG90 Eye Servo
       │   │
       │   └────(Voltage Divider 680Ω+1KΩ)──> DFPlayer RX
       │                                        (3.3V logic)
       ▼
   +──────────+
   │ PIR      │
   │ HC-SR501 │ (D2, sensitivity dial set CW, 60s warm-up)
   +──────────+
```

---

## Design Details

**Non-Blocking State Machine.** No `delay()` calls. Servo updates, PIR polling, and jaw animation all run from `millis()` timers in the main loop. Prevents stuttering when multiple subsystems update concurrently.

**Syringe Hydraulics.** A MG996R servo pushes a 60ml master syringe; fluid travels through 3/16" PVC tubing to a slave syringe that lifts the neck. The linkage uses a popsicle stick connecting the servo horn to the plunger, aligned for straight-line push. Quieter than a direct gear drive.

**Power Separation.** The Arduino runs from USB (5V). The three MG996R servos run from a 4×AA battery pack (~6V). A 1000µF capacitor across the servo rail buffers current spikes. Arduino and battery pack share a common ground.

**DFPlayer Integration.** The DFPlayer Mini's RX line expects 3.3V logic. A voltage divider (680Ω from Arduino TX to junction, 1KΩ from junction to ground, DFPlayer RX at junction) drops the 5V signal to ~2.98V. Audio files must be named `0001_...` inside a folder called `mp3` on a FAT32 SD card.

**PIR Sensor.** The HC-SR501 sensitivity potentiometer is turned clockwise (higher sensitivity). A mandatory 60-second warm-up period after power-on prevents erratic triggering during setup.

---

## Directory Structure

*   [`tsa-north-star-animatronic.ino`](./tsa-north-star-animatronic.ino) — Main sketch
*   [`/src`](./src/) — Modular C++ classes
    *   `StateEngine`: FSM coordinator
    *   `Actuators`: Servo wrapper with velocity ramping
    *   `Sensors`: PIR temporal debounce
    *   `AudioController`: DFPlayer serial protocol
*   [`/hardware`](./hardware/) — BOM, schematics, mechanical guide
    *   [`bom.md`](./hardware/bom.md): Parts list, pin map, power budget
    *   [`schematics/system_schematic_ascii.txt`](./hardware/schematics/system_schematic_ascii.txt): Wiring schematic
*   [`/docs`](./docs/) — Build log, failure analysis, competition notes
    *   [`postmortem_failure_log.md`](./docs/postmortem_failure_log.md): Every problem encountered and what fixed it
    *   [`voltage_drop_analysis.md`](./docs/voltage_drop_analysis.md): Brownout analysis and capacitor sizing
    *   [`competition_math.md`](./docs/competition_math.md): TSA rubric notes and design trade-offs

---

## Troubleshooting Summary

The [Postmortem Failure Log](./docs/postmortem_failure_log.md) covers the nine problems that came up during the build:

| Problem | Root Cause | Fix |
|---------|-----------|-----|
| Hydraulic leak | Wrong tubing (1/4" instead of 3/16") | Correct tubing |
| Joint stalls mid-lift | Air bubbles in line | Slow-cycle + tap to bleed |
| Sluggish tilt | Linkage angle off | Realigned for straight push |
| Random PIR triggers | Sensitivity too low | Turned dial CW |
| Erratic PIR at startup | No warm-up | 60s delay after power-on |
| DFPlayer silent | Wrong voltage divider resistors | 680Ω + 1KΩ rebuild |
| DFPlayer silent | Bad filename | 0001_ prefix, FAT32 card |
| Arduino resets mid-run | Servos on 5V pin | Moved to 4×AA 6V rail |
| Arduino resets mid-run | No transient buffer | 1000µF capacitor on servo rail |

---

## Build & Install

1. Open [`tsa-north-star-animatronic.ino`](./tsa-north-star-animatronic.ino) in Arduino IDE.
2. Install the `Servo` library (bundled with Arduino IDE).
3. Connect Arduino Uno via USB. Select **Tools > Board > Arduino Uno**, choose the port.
4. Compile and upload.
5. Open Serial Monitor at **115200 baud** to observe FSM state transitions.
6. **PIR warm-up:** wait 60 seconds after power-on before testing.