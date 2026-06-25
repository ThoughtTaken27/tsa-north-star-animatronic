# Fluid Power System: Syringe Hydraulics

Notes on the master-slave syringe mechanism used for neck tilt.

---

## System Diagram

```
  [MG996R Servo] ──> (Popsicle Stick Linkage) ──> [Master Syringe (60ml)]
                                                        │
                                                  [PVC Tubing] (3/16" ID)
                                                        │
  [Neck U-Joint] <── (Linkage) <─── [Slave Syringe (60ml)]
```

## How It Works

The MG996R servo horn pushes the master syringe plunger via a popsicle stick linkage. Fluid travels through PVC tubing to the slave syringe, which extends and tilts the neck pivot. The linkage must push in a straight line along the plunger axis — any angle wastes torque.

### Volume & Area

The 60ml syringe has a ~28.5mm piston inner diameter, giving a cross-sectional area of roughly 6.38 × 10⁻⁴ m². A 35mm plunger travel displaces approximately 22ml of fluid.

## Problems Encountered

1. **Wrong tubing size** — 1/4" ID used initially instead of 3/16" ID. Fixed by ordering the correct tubing.
2. **Air bubbles in the line** — caused the joint to stall mid-lift. Fixed by slow-cycling the servo while tapping the line to bleed air.
3. **Linkage angle** — the popsicle stick was pushing at an angle, wasting torque. Fixed by repositioning the syringe mount for straight-line push.

## Fluid

Distilled water with blue food coloring for visibility. No special additives required for a display that runs for minutes at a time.