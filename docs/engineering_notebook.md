# Engineering Notebook Diary — "The North Star"

This diary summarizes the daily development log, team structure, and milestone timelines for the design and construction of "The North Star" animatronic Harriet Tubman bust.

---

## 1. Team Structure & Allocations

The project was executed under a strict division of labor across a 3-person team:

- **Lead Systems Architect & Team Captain (Parth Khavate):** Responsible for electrical power engineering, low-level asynchronous firmware development, hydraulic-mechanical design, and overall systems integration.
- **Mechanical Designer (Team Member 2):** Focused on laser-cut MDF frame assembly, universal joint (U-joint) mounting, and structural bone proportions of the skull.
- **Creative Lead & Textile Designer (Team Member 3):** Handled soft silicone paintwork, facial historical accuracy, hair styling, and sewing period textiles.

---

## 2. Milestone Timeline

```text
  Week 1-2      Week 3-4      Week 5-6      Week 7-8      Week 9-10
+────────────+────────────+────────────+────────────+────────────+
│ Design &   │ Breadboard │ Mechanical │ Fluid Link │ System     │
│ Planning   │ Prototypes │ Assembly   │ Integration│ Calibration│
│ Phase      │ & Firmware │ (MDF frame)│ & Debugging│ & Defense  │
+────────────+────────────+────────────+────────────+────────────+
```

### Weeks 1–2: Research & Feasibility Phase
- **Action:** Selected Harriet Tubman "The North Star" theme. Assessed mechanical degrees of freedom needed.
- **Deliverable:** Created initial system-level blocks. Calculated torque limits for the MG996R servos and estimated total physical power limits.

### Weeks 3–4: Electrical Prototyping & Software Core
- **Action:** Wired the Arduino Uno R3 on a breadboard. Initialized SoftwareSerial communication with the DFPlayer Mini. Wrote the basic non-blocking state machine loop.
- **Deliverable:** Verified PIR sensor detection limits and validated basic serial command packet transmission.

### Weeks 5–6: Frame Construction & Actuator Rigging
- **Action:** Assembled the laser-cut MDF torso cage. Mounted the aluminum dual-axis neck U-joint. Fitted the internal 3D-printed skull cap with eye-shifter and jaw linkages.
- **Deliverable:** Initialized physical servo alignments and calibrated software boundaries to prevent mechanical collisions.

### Weeks 7–8: The Hydraulic System & Debugging Phase
- **Action:** Constructed the closed-loop hydraulic link using clear PVC tubing and 60ml Luer Lock master-slave syringes. Experienced immediate fluid seal blowouts and system brownouts.
- **Deliverable:** Solved the brownout reset loops by splitting the power rails and soldering a 1000µF decoupling capacitor. Solved hydraulic pressure loss by machining Delrin plunger heads with double nitrile O-rings.

### Weeks 9–10: Presentation Prep & Calibration
- **Action:** Mounted the silicone skin painted in historical likeness. Applied dry PTFE lubricant on structural neck joints to reduce skin friction. Polished the technical documentation.
- **Deliverable:** Executed continuous stress-testing. Prepared oral presentations for the judges' evaluation panel. Passed with zero mechanical or electrical failures during competition runs.
