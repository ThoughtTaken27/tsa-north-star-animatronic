# Competition Strategy & Math Analysis — "The North Star"

Winning a technical competition requires optimization of the scoring rubric. This document details the mathematical breakdown of the Technology Student Association (TSA) Animatronics rubric and how we engineered our system architecture to maximize points.

---

## 1. Rubric Distribution Analysis

The competition score is weighted across three main performance pools:

$$\text{Total Score} = \text{Functionality} \, (70\%) + \text{Engineering Documentation} \, (15\%) + \text{Presentation} \, (15\%)$$

| Evaluation Pool | Weight | Focus Areas | Our Engineering Response |
| :--- | :---: | :--- | :--- |
| **Functionality** | **70%** | Mechanical fluid movement, sequence timing, lip-sync accuracy, trigger reliability, physical durability | Asynchronous state machine (FSM), isolated dual power bus, robust double O-ring medical syringe hydraulics |
| **Documentation** | **15%** | Design drawings, wiring schematics, code logic, bill of materials, safety logs | Comprehensive 3-part technical portfolio (BOM, assembly schematics, failure logs) |
| **Presentation** | **15%** | Creative delivery, historical coherence, team coordination, answering judges' questions | Rigorous technical defense demonstrating first-principles troubleshooting (the 87 fixes) |

---

## 2. Optimizing the 70% Functionality Bottleneck

Because 70% of the grade depends on physical performance during judges' evaluation runs, we treated system reliability as our primary engineering target.

### The MTBF (Mean Time Between Failures) Strategy
Hobbyist teams focus on "feature creep"—adding secondary servos (e.g., ear wiggles, multi-joint hand grips). However, in embedded systems, every extra joint introduces:
- Linear increase in current draw (voltage sag risk).
- Quadratic increase in mechanical collision opportunities.
- Linear increase in wiring complexity (EMI noise risk).

**The Decision:** We restricted the system to four high-quality, high-reliability degrees of freedom (Neck Yaw, Neck Pitch, Mouth, Eyes). This simplified current pathways, stabilized our power rails, and allowed us to concentrate on achieving perfect lip-syncing and fluid hydraulic movement.

### Lip-Sync Coordination Calculations
To simulate speech, the mouth servo must respond to narrative audio track files instantly. 
- The DFPlayer Mini reads MP3 track files from an SD card.
- We mapped the voice track duration and calculated syllable pacing.
- The jaw control loop runs on a fast 120-millisecond update window:
  $$\Delta t_{\text{update}} = 120\,\text{ms}$$
- This sample rate is fast enough to match standard speech patterns without overloading the ATmega328P processor or stalling the MG996R servo gears.

---

## 3. Optimizing the 15% Documentation Pool

To secure maximum documentation points, we formatted the engineering files to align with professional industry standards rather than basic high-school notebooks. 

*   **Explicit Electrical Schematics:** Rather than simple Fritzing screenshots, we provided structured ASCII wire mapping and a complete power budget calculation.
*   **The Postmortem Failure Log:** By chronicling our 87 revisions and categorizing them into four engineering failure classes, we proved systematic design iteration. This detail shifted our documentation score from "proficient" to "exemplary."
