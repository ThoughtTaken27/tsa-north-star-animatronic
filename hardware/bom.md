# Bill of Materials & Pin Map — "The North Star"

This document outlines the complete bill of materials (BOM), electrical connections (Pin Map), and power budget for "The North Star" Harriet Tubman animatronic bust.

---

## Bill of Materials (BOM)

The physical system uses off-the-shelf components modified for custom mechanical linkages.

| Part Name | Model/Spec | Qty | Unit Cost | Source | System Role | Operating Voltage | Current Draw (Idle / Peak) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Microcontroller** | Arduino Uno R3 (ATmega328P) | 1 | $23.00 | Arduino | Core system logic and timing coordination | 5.0V | 45mA / 50mA |
| **High-Torque Servo** | TowerPro MG996R | 3 | $7.50 | Amazon | Neck Yaw, Neck Pitch (hydraulic), Jaw Move | 6.0V | 10mA (idle) / 2.5A (stall) |
| **Standard Servo** | SG90 Micro Servo | 1 | $3.00 | Amazon | Actuating light linkage (Eye Move) | 5.0V | 5mA (idle) / 650mA (stall) |
| **Audio Module** | DFPlayer Mini MP3 Player | 1 | $4.50 | Amazon | Storing and playing voice sequence | 5.0V | 15mA (idle) / 500mA (peak speaker load) |
| **SD Card** | 16GB MicroSD (Patriot) | 1 | $5.00 | Amazon | Stores MP3 audio files in folder named "mp3" on FAT32 | N/A | N/A |
| **Motion Sensor** | HC-SR501 PIR Sensor | 1 | $2.50 | Adafruit | Detecting user presence to trigger the sequence | 5.0V | 50µA / 15mA |
| **Speaker** | 8 Ohm, 3W, 2-inch | 1 | $4.00 | Adafruit | Audio output for voice files | 5.0V | N/A (passive) |
| **Piston Syringes** | 60ml Luer Lock Medical Syringe | 2 | $1.50 | Local supplier | Hydraulic actuators for neck tilt | N/A | N/A |
| **PVC Tubing** | 3/16" ID Clear Vinyl Tubing | 1m | $2.00 | Hardware store | Fluid transmission line between syringes | N/A | N/A |
| **Popsicle Sticks** | Standard Craft Sticks | 3 | $0.10 | Craft store | Linkage connectors between servo horns and syringe plungers | N/A | N/A |
| **Hydraulic Fluid** | Distilled Water with Blue Food Coloring | 0.5L | $1.00 | Grocery store | Fluid medium for syringe actuation | N/A | N/A |
| **Decoupling Capacitor** | 1000µF 25V Electrolytic | 1 | $0.50 | DigiKey | Buffering voltage drops on servo power rail during acceleration | N/A | N/A |
| **Voltage Divider Resistor** | 680Ω Metal Film | 1 | $0.05 | DigiKey | Voltage divider for DFPlayer RX (3.3V logic from 5V Arduino) | N/A | N/A |
| **Voltage Divider Resistor** | 1KΩ Metal Film | 1 | $0.05 | DigiKey | Voltage divider ground leg for DFPlayer RX line | N/A | N/A |
| **Battery Pack** | 4×AA Battery Holder | 1 | $2.00 | Amazon | 6V servo power supply (4 × 1.5V AA batteries) | 6.0V | N/A |

*Total Estimated Hardware Cost: ~$67.75*

---

## Pin Mapping

The Arduino Uno R3 coordinates inputs and outputs using the following electrical layout.

| Arduino Pin | Pin Function | Component Connected | Signal Type | Description |
| :---: | :--- | :--- | :--- | :--- |
| **D2** | Input (Digital) | HC-SR501 PIR Sensor (OUT) | Digital Logic | Triggers narrative sequence when state goes HIGH |
| **D5** | Output (PWM) | TowerPro MG996R (Neck Yaw) | PWM Signal | Coordinates left/right head pan movement |
| **D6** | Output (PWM) | TowerPro MG996R (Neck Pitch/Tilt) | PWM Signal | Drives mechanical syringe linkage for neck rise/fall |
| **D9** | Output (PWM) | TowerPro MG996R (Jaw Move) | PWM Signal | Drives jaw linkage synced with speaker audio |
| **D10** | Output (Software RX) | DFPlayer Mini (TX) | Serial (9600 bps) | Reads state feedback and command acknowledgments from audio module |
| **D11** | Output (Software TX) | DFPlayer Mini (RX) via 1kΩ | Serial (9600 bps) | Sends track selection, volume controls, and play/stop commands |
| **D12** | Output (Digital) | SG90 Micro Servo (Eye Move) | PWM Software | Coordinates side-to-side eye shifting during sequence |

---

## Power Budget Analysis

Unregulated power routing to high-torque servos is the primary cause of system resets in multi-servo animatronics. The power design isolates logic from load.

### Core Calculations

1. **Logic Rail (5V):**
   - Arduino Uno R3: 45mA
   - DFPlayer Mini (idle): 15mA
   - HC-SR501 PIR: 15mA
   - **Total Standard Logic Current:** **75mA**
   - Peak Audio Playback (3W Speaker peak): **500mA**
   - *Logic Rail Peak Load: 575mA* (easily handled by 5V 1A logic supply).

2. **Motor Rail (6V):**
   - 3x MG996R Servos (moving simultaneously, mid-load): `3 * 1.2A = 3.6A`
   - 3x MG996R Servos (stall limit peak): `3 * 2.5A = 7.5A`
   - SG90 Micro Servo (peak load): **650mA**
   - **Total Peak Motor Load:** **4.25A** (during sequence initiation when multiple joints accelerate from rest).

### Power Architecture

The Arduino is powered via USB (5V from laptop, phone charger, or USB power bank). The three MG996R servos draw power from a dedicated 4×AA battery pack (1.5V × 4 = 6V). The Arduino and battery pack share a common ground connection to keep signal references in sync.

- **Servo Power:** 4×AA battery holder outputting ~6V. Batteries provide enough current for the MG996R servos under mid-load without pulling down the Arduino's 5V rail.
- **Common Ground:** Arduino GND connected to battery pack GND — required so PWM signals share a reference.
- **Capacitive Buffering:** A 1000µF 25V electrolytic capacitor wired across the servo power rail to buffer transient current spikes during servo acceleration.
