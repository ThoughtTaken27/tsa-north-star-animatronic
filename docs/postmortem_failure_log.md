# Engineering Postmortem & Failure Log — "The North Star"

Real engineering lives in the debugging logs. During the 2-month build cycle, "The North Star" animatronic underwent 87 distinct revisions to move the system from unstable prototype to a highly reliable, 1st-place state championship build. 

This postmortem analyzes the four primary failure classes encountered, detailing the physical symptoms, the investigative hypotheses, diagnostic tests, and the final engineering solutions.

---

## Failure Class 1: Electrical Power Stability (Brownouts & Voltage Drops)

### 1. Symptom
The system random-restarts or freezes mid-sequence, particularly when the neck tilt (hydraulic) and yaw servos accelerate simultaneously. The DFPlayer Mini sound module drops audio and clicks before the Arduino resets to the setup block.

### 2. Hypothesis
The dual MG996R servos pull high inrush current during rapid speed changes. This sudden demand drags down the common power rail voltage below the ATmega328P microcontroller's brownout detection (BOD) threshold of 4.3V, triggering a CPU reset.

### 3. Diagnostics
- **Equipment:** Rigol DS1102Z Digital Oscilloscope.
- **Method:** Probe the 5V logic rail at the Arduino VCC pin during a dual-servo sweep.
- **Results:** Observed a sharp transient voltage dip (sag) down to 3.6V lasting for 45 milliseconds during simultaneous servo acceleration. This dip verified the power rail sag as the direct cause of the ATmega328P reset state.

```text
Volts
 5.0V ──────┬────────────────────┬────────
            │                    │
 4.3V ──────┼─── BOD Threshold ──┼──────── (Reset triggers here)
            │  \              /  │
 3.6V ──────┼───\── Sag Dip ─/───┼──────── 
            └─── 45ms Transient ─┘
 0.0V ────────────────────────────────────
                                  Time (ms)
```

### 4. Mitigations & Solutions
- **Rail Isolation:** Separated the power rails entirely. Placed the logic components (Arduino, PIR sensor, audio module) on an isolated 5V 2A regulator circuit. Placed the four inductive servo loads on a high-current 6V 5A power bus.
- **Ground Ring Connection:** Linked the two ground paths at a single point (star ground configuration) on the main power terminal block to prevent ground loops.
- **Bulk Capacitive Reservoirs:** Added a 1000µF 16V low-ESR electrolytic capacitor in parallel directly across the 6V motor power distribution rail to buffer the current spikes. Added a 470µF decoupling capacitor on the 5V logic line immediately adjacent to the DFPlayer Mini power inputs to prevent audio amplification spikes from feeding noise back to the MCU.

---

## Failure Class 2: Electromagnetic Interference (EMI) & Sensor False Triggers

### 1. Symptom
The animatronic triggers its speaking sequence randomly when no human is present in the detection zone. This phantom triggering occurs primarily when the neck servos move during calibration runs.

### 2. Hypothesis
The HC-SR501 PIR sensor has high input impedance. Electromagnetic noise radiated from the DC motor brushes inside the MG996R servos couples inductively into the unshielded 1.5-meter PIR signal line, generating false HIGH logic levels at Arduino digital pin D2.

### 3. Diagnostics
- **Method:** Covered the PIR sensor lens with black electrical tape to block infrared changes. Run the neck servos continuously. Monitor the state of pin D2 via serial stream.
- **Results:** Observed digital pin D2 flickering between `0` and `1` in sync with servo PWM switching, proving EMI was coupling into the signal path.

### 4. Mitigations & Solutions
- **Shielded Cabling:** Replaced standard hookup wire with shielded twisted-pair (STP) cable for the PIR sensor connection, grounding the shield drain wire solely at the Arduino chassis ground.
- **Input Node Stiffening:** Wired a physical 10kΩ metal-film pull-down resistor between digital pin D2 and ground. This reduced the node impedance, draining coupled low-energy induced charges to ground before they could cross the 3.0V logic HIGH threshold.
- **Software Debounce & Window Filtering:** Rewrote the sensor polling code to implement a temporal logic filter. The software now requires the PIR state to remain high for 150 consecutive milliseconds before confirming a true human presence event.

---

## Failure Class 3: Mechanical Friction & Skin Tension Binding

### 1. Symptom
The neck pitch movement is jerky and sluggish. The servo hums loudly (groaning under continuous stall-current load of ~2.2A) and runs hot to the touch. The motion of the neck is asymmetrical between rising and falling phases.

### 2. Hypothesis
The heavy silicone skin of the bust is stretched tightly over the mechanical frame. The latex neck joints exert variable elastic tension during movement, exceeding the MG996R servo’s maximum rated torque of 11 kg/cm.

### 3. Diagnostics
- **Method:** Disconnect the silicone skin entirely and execute the motion sequence. Reconnect the skin and measure current draw on the 6V motor rail.
- **Results:** 
  - Without skin: Servo current draw = 220mA (normal operational load); movement is fluid.
  - With skin: Servo current draw = 1.9A to 2.3A (continuous stall condition); movement is severely restricted.

### 4. Mitigations & Solutions
- **Skin Tension Relief:** Slit the internal back layer of the silicone throat piece to introduce mechanical relief pockets. This modification allows the skin to expand during neck tilt rather than stretching.
- **Mechanical Lubrication:** Coated the structural aluminum neck U-joint in dry-film PTFE (teflon) spray lubricant. Unlike grease, dry teflon does not attract dust or degrade the silicone skin material.
- **Software Velocity Ramping:** Replaced instant angular steps (`servo.write(angle)`) with an active speed ramping routine. The firmware now increments the angle position incrementally every 15 milliseconds using a cosine-shaped acceleration curve, matching mechanical inertia and reducing start-up torque demands.

---

## Failure Class 4: Hydraulic Pressure Decay & Seal Degradation

### 1. Symptom
Over 48 hours of display testing, the neck tilt joint loses height (head droops). The linear extension under load diminishes, and blue liquid deposits appear around the master syringe shafts.

### 2. Hypothesis
The standard medical-grade rubber plunger seals degrade when exposed to continuous pressure and color additives. Fluid leaks past the single seal line, causing pressure drop and hydraulic volume loss.

### 3. Diagnostics
- **Method:** Apply a static mechanical load to the master syringe plunger and inspect the rear seal boundary over a 12-hour window.
- **Results:** Observed a steady fluid leakage rate of ~0.5ml per hour past the primary rubber seal, accompanied by a 4mm drop in slave syringe linear extension.

### 4. Mitigations & Solutions
- **Dual O-Ring Plunger Modification:** Removed the default single-contact rubber plungers. Machined two grooved slots into custom-turned Delrin plunger heads. Fitted them with dual nitrile O-rings lubricated with high-viscosity silicon grease to establish a pressure-tight dynamic seal.
- **Fluid Reformation:** Replaced standard tap water with a 20/80 mix of industrial propylene-glycol and distilled water. Glycol preserves seal elasticity, prevents internal oxidation of aluminum fittings, and acts as a mild lubricant for the tubing walls.
- **Software Zeroing Check:** Added a "re-calibration" phase in the state machine. Every time the system returns to its idle state, the pitch servo drives the master plunger slightly beyond the home baseline for 200ms to rebuild pressure and purge tiny air gaps back to the master reservoir.
