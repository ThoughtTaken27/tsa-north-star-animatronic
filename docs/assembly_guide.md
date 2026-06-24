# Mechanical Assembly & "Hydraulic Hack" Guide — "The North Star"

This guide details the physical build process, material selection, mechanical limits, and custom hydraulic syringe actuator setup used for "The North Star" animatronic bust.

---

## 1. Frame Structure & Material Selection

The mechanical skeleton of the Harriet Tubman bust balances weight constraints with structural rigidity. High weight on the moving head assemblies causes servo stalling and joint deflection.

### Material Specifications
- **Core Chassis:** 6mm thick medium-density fiberboard (MDF) laser-cut into a rigid box frame to act as the ribcage and shoulder mount.
- **Head Skeleton:** 3D-printed internal skull cap (PLA, 15% infill, 3 perimeters) to secure mounting points for the eye-shifter and jaw servos.
- **Skin Layer:** Soft-pour platinum-cured silicone shell painted to match historical likeness.
- **Neck Pivot:** Dual-axis universal joint (U-joint) machined from aluminum. This isolates rotational forces (Yaw) from linear tilt forces (Pitch).

---

## 2. The Hydraulic Fluid Power Hack

To achieve silent, smooth neck rise-and-fall movement without the loud gear whining of mechanical linear actuators, the system uses a custom closed-loop hydraulic-mechanical link.

```text
       [MG996R Servo]
              │
         (Servo Horn)
              │
        (Linkage Arm)
              │
   ┌──────────┴──────────┐
   ▼                     ▼
[Plunger]             [Plunger]
[60ml Master Syringe] [60ml Master Syringe]
   │                     │
   └──(Clear PVC Tube)───┘
   │                     │
   ▼                     ▼
[60ml Slave Syringe]  [60ml Slave Syringe]
   │                     │
   └──────────┬──────────┘
              ▼
       [Neck Tilt U-Joint]
```

### Fluid Link Specifications
- **Master Syringes (Driver):** Two 60ml Luer Lock medical-grade polypropylene syringes mounted inside the torso frame.
- **Slave Syringes (Driven):** Two matching 60ml syringes mounted vertically behind the neck U-joint.
- **Transmission Lines:** 4.8mm (3/16 inch) inner diameter clear PVC tubing secured to syringe Luer lock tips with stainless steel zip-ties.
- **Fluid Medium:** Distilled water mixed with blue-tinted water-glycol food coloring. The blue dye provides visual confirmation of fluid path continuity and flow velocity. Water-glycol prevents internal microbial growth and lubricates plunger seals.

### Plunger-Servo Linkage
1. **Mechanical Leverage:** The plunger of the master syringe connects to the horn of the MG996R servo via an adjustable threaded M3 aluminum linkage rod.
2. **Double O-Ring Seal:** Polypropylene syringes tend to bleed pressure past standard single rubber seals under continuous load. The master and slave plungers are retrofitted with custom-greased double nitrile O-rings (15mm ID, 2.5mm width) to ensure air-tight, water-tight boundaries.
3. **Piston Displacement math:** The MG996R has an effective 120-degree sweep under control. This rotational sweep drives the plunger through a 35mm linear displacement, translating to ~12ml of fluid movement. This displacement is sufficient to tilt the neck joint up to 25 degrees.

---

## 3. Servo Alignment & Calibration Limits

Never map standard RC servos to full physical limits (`0` to `180` degrees) directly in software. This can result in structural binding, linkage collisions, and high stall-current draws.

Before mounting linkages, flash the calibration sketch and mechanical alignments to the physical center limits below:

| Joint Assembly | Servo Model | Servo ID | Mechanical Minimum | Software Safe Min | Software Safe Center | Software Safe Max | Mechanical Maximum | Action Trigger / Path |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| **Neck Yaw** | MG996R | `YAW` | 15° | 30° | 90° | 150° | 165° | Head Pan Left/Right (Scanning) |
| **Neck Pitch** | MG996R | `PITCH`| 40° | 50° | 95° | 140° | 150° | Hydraulic Neck Tilt Up/Down |
| **Jaw Move** | MG996R | `JAW` | 10° | 20° | 55° | 90° | 105° | Voice Sync (Mouth Opening) |
| **Eye Shift** | SG90 | `EYE` | 30° | 45° | 90° | 135° | 150° | Saccadic Side-to-Side Motion |

### Mechanical Calibration Protocol
1. **Center Servos:** Write `90` to all servo channels using the calibration firmware before connecting structural linkages.
2. **Mount Linkages:** Secure the linkage rods to the horns while the joints are in their physical home positions (e.g., neck straight, jaw fully closed, eyes centered).
3. **Sweep Limits Test:** Manually increment the servo pulse-widths in 5-degree steps. Watch for structural flexing or current draw spikes on the power supply. If current draw exceeds 1.5A per active motor during slow sweeps, reduce the software safe limits to eliminate mechanical binding.
