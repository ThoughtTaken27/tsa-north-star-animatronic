# Bill of Materials & Pin Map — "The North Star"

This document outlines the complete bill of materials (BOM), electrical connections (Pin Map), and power budget for "The North Star" Harriet Tubman animatronic bust.

---

## Bill of Materials (BOM)

The physical system uses off-the-shelf components modified for custom mechanical linkages.

| Part Name | Model/Spec | Qty | Unit Cost | Source | System Role | Operating Voltage | Current Draw (Idle / Peak) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Microcontroller** | Arduino Uno R3 (ATmega328P) | 1 | $23.00 | Arduino | Core system logic and timing sequence coordination | 5.0V | 45mA / 50mA |
| **High-Torque Servo** | TowerPro MG996R | 3 | $7.50 | Amazon | Actuating heavy mechanical linkages (Neck Pitch, Neck Yaw, Jaw Move) | 6.0V | 10mA (idle) / 2.5A (stall) |
| **Standard Servo** | SG90 Micro Servo | 1 | $3.00 | Amazon | Actuating light linkage (Eye Move) | 5.0V | 5mA (idle) / 650mA (stall) |
| **Audio Module** | DFPlayer Mini MP3 Player | 1 | $4.50 | Amazon | Storing and playing voice sequences and background track | 5.0V | 15mA (idle) / 500mA (peak speaker load) |
| **Motion Sensor** | HC-SR501 PIR Sensor | 1 | $2.50 | Adafruit | Detecting user presence to trigger the sequence | 5.0V | 50µA / 15mA |
| **Speaker** | 8 Ohm, 3W, 2-inch | 1 | $4.00 | Adafruit | Audio output for voice files | 5.0V | N/A (passive) |
| **Piston Syringes** | 60ml Luer Lock Medical Syringe | 2 | $1.50 | Local supplier | Custom hydraulic actuators for smooth neck tilt movement | N/A | N/A |
| **Hydraulic Fluid** | Distilled Water + Water-Glycol Dye | 1L | $2.00 | Hardware store | Fluid medium for linear syringe actuation | N/A | N/A |
| **Decoupling Capacitor** | 1000µF 16V Electrolytic | 2 | $0.50 | DigiKey | Buffering voltage drops on motor power rails during rapid acceleration | N/A | N/A |
| **Pull-down Resistor** | 10k Ohm Metal Film | 1 | $0.05 | DigiKey | Stiffening PIR sensor output against EMI noise | N/A | N/A |
| **Inline Resistor** | 1k Ohm Metal Film | 2 | $0.05 | DigiKey | Reducing current and noise on TX/RX SoftwareSerial lines | N/A | N/A |
| **Power Supply** | 5V/6V Dual Output AC-DC Adapter | 1 | $15.00 | Amazon | Isolated supplies: 5V for logic, 6V (3A peak) for motors | N/A | N/A (wall supply) |

*Total Estimated Hardware Cost: ~$74.15*

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

### Isolation Strategy

To protect the ATmega328P microcontroller from logic resets (brownouts) caused by inductive motor spikes and massive current draw:
- **Separate Transformers:** The AC-DC adapter delivers two isolated rails: a 5V supply dedicated solely to the Arduino and the DFPlayer Mini, and a 6V 5A power rail dedicated to the motor terminal blocks.
- **Common Ground:** The 5V logic ground and 6V motor ground connect at a single point (star ground) near the Arduino power jack. This prevents ground loops and reference float.
- **Capacitive Buffering:** A 1000µF electrolytic capacitor is wired in parallel directly across the 6V motor power distribution rail to supply instantaneous current during high-acceleration spikes, preventing local voltage sag.
