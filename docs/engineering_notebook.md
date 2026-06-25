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
- **Action:** Assembled the laser-cut MDF torso cage. Mounted the neck U-joint. Fitted the internal frame with eye-shifter and jaw linkages.
- **Deliverable:** Initialized physical servo alignments and calibrated software boundaries to prevent mechanical collisions.

### Weeks 7–8: The Hydraulic System & Debugging Phase
- **Action:** Constructed the hydraulic link using PVC tubing and 60ml syringes. Fought three problems: wrong tubing size (1/4" instead of 3/16" ID), air bubbles in the line, and popsicle stick linkage at the wrong angle. Brownouts started appearing when servos fired simultaneously during testing.
- **Deliverable:** Fixed hydraulics by switching to correct 3/16" tubing, bleeding air, and realigning linkage. Fixed brownouts by moving servo power to a dedicated 4×AA battery pack and adding a 1000µF capacitor. Solved DFPlayer audio by rebuilding the voltage divider (680Ω + 1KΩ) and correcting the file naming convention.

### Weeks 9–10: Presentation Prep & Calibration
- **Action:** Mounted the silicone skin. Applied PTFE lubricant on structural neck joints to reduce friction. Polished the technical documentation.
- **Deliverable:** Executed continuous stress-testing. Prepared oral presentations for the judges' evaluation panel. Passed with zero mechanical or electrical failures during competition runs.
