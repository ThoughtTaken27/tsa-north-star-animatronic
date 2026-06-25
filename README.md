# "The North Star" — Harriet Tubman Animatronic Bust

[![Shield: 1st Place](https://img.shields.io/badge/Competition-1st%20Place%20State%20Championship-gold.svg?style=flat-square)](https://github.com/parthkhavate/tsa-north-star-animatronic)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino%20Uno-blue.svg?style=flat-square)](https://www.arduino.cc/)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B%20%2F%20Embedded-brightgreen.svg?style=flat-square)](https://isocpp.org/)

"The North Star" is a fully custom, interactive animatronic Harriet Tubman bust built over a intensive two-month design cycle. The system won **1st Place at the Tennessee TSA State Championship (2026)**.

The project demonstrates systems-level embedded engineering, real-time asynchronous firmware development, fluid dynamics (using a custom closed-loop hydraulic cylinder system), and precise mechanical motion syncing.

---

## Technical Overview & Core Stats

| Metric | Specification |
| :--- | :--- |
| **Primary Outcome** | **1st Place, Tennessee State Championship (May 2026)** |
| **System Integrator & Role** | Parth Khavate — Lead Systems Architect, Team Captain |
| **Total Engineering Effort** | ~200 hours (Design, Assembly, Calibration, Debugging) |
| **Microcontroller** | ATmega328P (Arduino Uno R3) |
| **Actuators** | 3x TowerPro MG996R High-Torque Servos, 1x SG90 Micro Servo |
| **Transmission Type** | Closed-Loop Hydraulic Syringe System (Neck Tilt) + Direct Mechanical Linkage |
| **Audio Interface** | DFPlayer Mini with 8-Ohm 3W Speaker via custom SoftwareSerial |
| **Sensor Interface** | HC-SR501 Passive Infrared (PIR) Sensor with temporal software debouncing |
| **Power Infrastructure** | Isolated Dual Power Supplies (5V Logic, 6V Motor Bus) with Star Ground |

---

## 1. System Architecture Diagram

Admissions readers can inspect how subsystems connect electrically and mechanically below:

```text
               +───────────────────────────────────+
               │        AC/DC WALL ADAPTER         │
               +───┬───────────────────────────┬───+
                   │ (5V Logic Power)          │ (6V Motor Power)
                   ▼                           ▼
       +───────────────────────+       +───────────────────────+
       │  5V LOGIC POWER BUS   │       │   6V MOTOR POWER BUS  │
       +─────┬───────────┬─────+       +───────────┬───────────+
             │           │                         │
             │           │ (Power Ring)            ▼
             ▼           │             +───────────────────────+
     +─────────────+     │             │ 1000uF Bulk Capacitor │
     │ ARDUINO UNO │     │             +───────────┬───────────+
     │  (ATmega)   │     │                         │ (Buffered 6V)
     +───┬───┬───┬─+     │                         ├───────────────────────┐
         │   │   │       │                         │                       │
         │   │   │       ▼                         ▼                       ▼
         │   │   │   +─────────────+       +───────────────+       +───────────────+
         │   │   └──>│ PIR SENSORS │       │ MG996R Servos │       │ SG90 Servo    │
         │   │       +─────────────+       │ (Yaw/Pitch/Mouth)     │ (Eye Shifter) │
         │   │       (Input Trigger)       +───────────────+       +───────────────+
         │   │                                     ▲                       ▲
         │   └───────────────(PWM Control Pins)────┼───────────────────────┘
         │
         ▼ (SoftwareSerial TX/RX via 1kΩ)
     +─────────────+
     │  DFPLAYER   ├───────────────> [ SPK ] ────> 8Ω 3W Passive Speaker
     │    MINI     │
     +─────────────+
```

---

## 2. Technical Breakthroughs

### The Asynchronous Finite State Machine (FSM)
To achieve natural coordination without mechanical stuttering, the firmware avoids blocking `delay()` statements entirely. Every sub-assembly (saccadic eye-shifting, syllable-synced jaw flapping, head panning, and smooth hydraulic neck tilting) runs concurrently using software millisecond timers (`millis()`).

### The "Hydraulic Hack"
Standard physical linear actuators are loud, expensive, and jerk under initial load. To coordinate smooth neck tilt, the system translates the rotational movement of a high-torque MG996R servo into linear motion using dual 60ml Luer Lock medical-grade master syringes. Fluid travels through reinforced clear PVC lines to matching slave syringes linked to the neck pivot, achieving silent, fluid lift movement.

### Star-Ground & Transient Buffering
Simultaneous servo acceleration pulls peak transient current spikes exceeding 4A. An isolated dual power-supply bus separates the sensitive logic elements (such as the ATmega328P and DFPlayer audio lines) from the heavy inductive loads of the motors. A 1000µF low-ESR electrolytic capacitor acts as a reservoir to buffer transient sag on the motor rail, eliminating CPU resets.

---

## 3. Directory Structure & Quick Navigation

The assets inside this repository are organized as follows:

*   [**`tsa-north-star-animatronic.ino`**](./tsa-north-star-animatronic.ino) — Main Arduino sketch, entry point, system setup, and non-blocking loop scheduler.
*   [**`/firmware`**](./firmware/) — Fully modular C++ code classes.
    *   [`StateEngine.h`](./firmware/StateEngine.h) / [`.cpp`](./firmware/StateEngine.cpp): The Finite State Machine coordinator (Idle -> Speaking -> Hydraulic Tilt -> Return to Home).
    *   [`Actuators.h`](./firmware/Actuators.h) / [`.cpp`](./firmware/Actuators.cpp): Custom servo wrapping class implementing velocity speed-ramping profiles.
    *   [`Sensors.h`](./firmware/Sensors.h) / [`.cpp`](./firmware/Sensors.cpp): Temporal filter class debouncing high-impedance PIR input lines.
    *   [`AudioController.h`](./firmware/AudioController.h) / [`.cpp`](./firmware/AudioController.cpp): Direct serial communicator managing MP3 playback command packets.
*   [**`/hardware`**](./hardware/) — Wiring diagrams, mechanical assemblies, fluid power physics, and budgets.
    *   [`bom.md`](./hardware/bom.md): Tabulated Bill of Materials, Arduino I/O pin mapping, and power budget profiles.
    *   [`mechanical_assembly.md`](./hardware/mechanical_assembly.md): Structural details, torso MDF frame, and neck universal joint rigging.
    *   [`fluid_power_system.md`](./hardware/fluid_power_system.md): Closed-loop master-slave syringe hydraulic cylinder calculations and O-ring seals.
    *   [`schematics/system_schematic_ascii.txt`](./hardware/schematics/system_schematic_ascii.txt): Detailed ASCII electrical schematic.
*   [**`/docs`**](./docs/) — Historical contexts, competition rubrics, and systematic failure logs.
    *   [`postmortem_failure_log.md`](./docs/postmortem_failure_log.md): Analysis of the 87 micro-fixes, categorized into four primary electrical, mechanical, electromagnetic, and fluidic engineering failures.
    *   [`voltage_drop_analysis.md`](./docs/voltage_drop_analysis.md): Deep-dive electrical report on transient voltage sags and capacitive decoupling.
    *   [`competition_math.md`](./docs/competition_math.md): Strategic optimization analysis of the high-weight scoring rubric.
    *   [`historical_context.md`](./docs/historical_context.md): Deep-dive on the historical background of Harriet Tubman and "The North Star" theme.
    *   [`engineering_notebook.md`](./docs/engineering_notebook.md): Timeline diary, team structure, and daily development log.
    *   [`assembly_guide.md`](./docs/assembly_guide.md): Quick-start physical calibration limits and hardware safe boundary rules.

---

## 4. Reconstructing the 87 Fixes

Real engineering is demonstrated by the ability to systematically troubleshoot physical systems. Our full [Postmortem Failure Log](./docs/postmortem_failure_log.md) chronicles how we solved the four primary challenges during assembly:

1.  **Logic Resets (Brownouts):** Solved by building a split-rail logic/motor power supply bus and wiring a 1000µF decoupling capacitor near the servo hub.
2.  **EMI Noise (Sensor False-Triggers):** Solved by replacing standard signal hookups with shielded twisted-pair cables and wiring a physical 10kΩ pull-down resistor to stiffen the input node.
3.  **Mechanical Binding (Silicone Friction):** Solved by slitting back pockets into the silicone throat skin, spraying dry-film PTFE (Teflon) on joint pivots, and writing software velocity ramp profiles in the firmware.
4.  **Hydraulic Droop (Pressure Loss):** Solved by machining Delrin plunger heads with dual O-rings and shifting to a distilled water-propylene glycol mixture.

---

## 5. Build & Installation

To flash the code and set up the diagnostic serial telemetry:

1.  Open [**`tsa-north-star-animatronic.ino`**](./tsa-north-star-animatronic.ino) in the Arduino IDE (or compile using the Arduino CLI).
2.  Install the standard `Servo` library.
3.  Connect the Arduino Uno R3 via USB.
4.  Select `Arduino Uno` under **Tools > Board** and choose your COM/Serial Port.
5.  Compile and Upload.
6.  Open the Serial Monitor and configure the baud rate to **`115200`** to monitor real-time FSM state change logging.
