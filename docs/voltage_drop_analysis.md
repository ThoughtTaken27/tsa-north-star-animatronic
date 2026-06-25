# Electrical Analysis: Voltage Drops & Power Stability

This document provides a rigorous electrical engineering analysis of the transient voltage drops (sags) and power rail instability encountered during the testing of "The North Star" animatronic, detailing the physics, diagnostics, and mathematical modeling behind the capacitive filtering solution.

---

## 1. The Physics of the Failure

The system uses three TowerPro MG996R high-torque servos. The electrical specifications of the MG996R are:
- **Operating Voltage:** 4.8V to 7.2V (6.0V optimal)
- **Idle Current:** 10mA
- **Running Current (no load):** 170mA
- **Stall Current (peak draw):** **2.5A at 6.0V**

### The Transient Inductive Current Peak
When a DC motor inside a servo starts from rest or changes direction rapidly, it behaves as a near short-circuit initially. The current draw spikes instantaneously to the stall limit:
$$I_{\text{peak}} = N \times I_{\text{stall}}$$
For three MG996R servos acting simultaneously under load, the peak current demand is:
$$I_{\text{peak}} = 3 \times 2.5\,\text{A} = 7.5\,\text{A}$$

Because the power lines have physical internal resistance ($R_{\text{wire}}$) and inductance ($L_{\text{wire}}$), this instantaneous current spike generates a transient voltage drop across the supply bus:
$$V_{\text{sag}} = I_{\text{peak}} \times R_{\text{wire}} + L_{\text{wire}} \frac{di}{dt}$$

If the logic components (such as the ATmega328P microcontroller) share this power bus, the voltage sag drops the logic rail below the microcontroller's **Brownout Detection (BOD) threshold of 4.3V**, causing the CPU to reset.

---

## 2. Diagnostic Oscilloscope Mapping

Using a Digital Storage Oscilloscope (DSO), we probed the logic supply line of the ATmega328P during a dual-servo rapid sweep.

```text
Volts (V)
 5.0V ───┬─────────────────────────────────┬───
         │                                 │
 4.3V ───┼── Brownout Threshold (Reset) ───┼───
         │ \                             / │
 3.6V ───┼───\─────────── Sag ──────────/──┼───
         └────\────────────────────────/───┘
              |<───── dt = 45ms ──────>|
 0.0V ─────────────────────────────────────────
                                          Time (ms)
```

The diagnostics revealed:
- **Steady State Voltage:** 5.01V
- **Transient Sag Minimum:** 3.62V
- **Sag Duration ($dt$):** 45 milliseconds
- **Result:** The 3.62V sag was deep enough and lasted long enough to trigger the ATmega328P hardware reset state, causing infinite loop restarts mid-motion.

---

## 3. The Capacitive Filtering Solution

To stabilize the power rail, we integrated a bulk **1000µF electrolytic decoupling capacitor** wired in parallel directly across the 6V motor power rail.

### Mathematical Modeling of Charge Discharge
The capacitor acts as a localized charge reservoir. When the servo motor starts, the capacitor discharges to supply the instantaneous inrush current, buffering the voltage drop on the main supply line.

The charge stored in the capacitor is calculated by:
$$Q = C \times V$$
For a $1000\,\mu\text{F}$ capacitor at $6.0\,\text{V}$:
$$Q = (1000 \times 10^{-6}\,\text{F}) \times 6.0\,\text{V} = 6.0 \times 10^{-3}\,\text{Coulombs}$$

The voltage drop ($\Delta V$) of a discharging capacitor over a transient duration ($dt$) under a current load ($I$) is modeled by:
$$\Delta V = \frac{I \times dt}{C}$$

By decoupling the logic supply rail from the motor power supply rail, and placing the bulk $1000\,\mu\text{F}$ capacitor on the motor rail, we effectively lowered the impedance of the power bus. The transient sag was reduced to less than **0.2V**, keeping the logic rail clean and stable.
