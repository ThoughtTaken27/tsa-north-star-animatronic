# Mechanical Assembly - "The North Star"

This document describes the supported mechanical build: a PVC-and-wood skeleton on a plywood base, with exposed electronics, servo-driven head motion, a two-syringe fluid power pointing arm, and a removable outer presentation layer.

**Naming convention:** "right arm" throughout this repository means the arm on the viewer's right as they face the exhibit. That is the syringe-driven pointing arm. The lantern arm is on the viewer's left and is the one the firmware calls `leftArmServo`.

## Base and Skeleton

- **Base:** roughly 12 x 12 in plywood platform, painted white, elevated on four short wooden dowel feet. Holds the Arduino/breadboard control stack, DFPlayer, PIR sensor, speaker, 9V battery, the switched 4xAA servo battery pack, and the drive half of the hydraulic system.
- **Spine:** A vertical 1/2 in PVC support rises from the base and carries the upper body.
- **Shoulders:** A PVC tee at the top of the spine with a horizontal pipe through it forms the shoulder crossbar, with 1/2 in fittings at the ends.
- **Head:** A painted foam ball head sits on a vertical wooden dowel driven by the head servo at the top of the PVC frame.
- **Removable shell:** Fabric/clothing sits over the skeleton and lifts off for judging. The shell has to be removable or the entry is not evaluated at all, so this is a hard requirement rather than a finish detail. Target removal time was under 10 seconds.

No frame dimensions beyond the base footprint and the 6 in foam ball are recorded, so none are stated here. The resting-position envelope the build had to satisfy is 15 in deep by 3 ft wide by 4 ft high.

## Motion Assemblies

### Head Turn

An MG996R servo mounted near the top of the PVC frame turns the foam head through a vertical dowel. This provides a clear "comes to life" motion without needing a complex jaw.

### Syringe-Driven Pointing Arm (Fluid Power)

This is the movement that satisfies the competition's fluid power requirement. Omitting fluid power is a 10-point deduction, so this subsystem is not decorative.

It is a closed two-syringe water circuit, master and slave:

1. **Drive syringe (master).** A 60 mL syringe lies horizontally on top of the plywood base, zip-tied down so it cannot twist. An MG996R servo, also on the base, rotates and pushes a short wooden dowel taped to its horn straight into the plunger flange.
2. **Tubing.** 3/16 in inner diameter clear vinyl tubing runs from the drive syringe nozzle up along the spine to the shoulder. Water was tinted so the fluid is visible moving through the clear tube during the demonstration.
3. **Output syringe (slave).** A second 60 mL syringe is mounted horizontally near the top of the spine, secured to the frame. Its nozzle takes the tubing; its plunger points outward toward the arm.
4. **Arm coupling.** The output syringe's plunger is coupled to the pointing arm dowel by a short wooden dowel link with a screw fitting. As water forces the plunger out, the link pushes the arm and the arm rotates upward.

Because water is effectively incompressible, servo rotation at the base transfers almost directly into plunger extension at the shoulder. Any trapped air breaks that, which is why the fill procedure is a real procedure and not a formality. See [`docs/postmortem_failure_log.md`](../docs/postmortem_failure_log.md) section 4.

**The shoulder pivot is unpowered.** The arm rotates on a plain metal pin through a drilled hole at the shoulder. The hole is slightly larger than the pin so the arm swings freely without binding while staying constrained to one axis. There is no motor, servo, or driven actuator at that joint. All the force comes from the fluid column below.

This is worth stating plainly because it is the point of the mechanism: judges asking "is that arm just a fourth servo?" get a hinge they can see and a fluid circuit they can trace.

Linkage alignment matters more than force. If the plunger or arm is pushed sideways, it binds and wastes servo torque.

### Lantern Arm

An SG90 micro servo is zip-tied directly to the end of the horizontal PVC shoulder crossbar and drives a wooden dowel arm downward from there. The arm carries a craft-stick lantern frame with a warm white LED inside it. The LED is on its own Arduino pin, separate from the servo, so the light can come on before or during the arm movement.

The servo is mounted with hot glue for placement and zip ties for load. Hot glue positions the part; the zip ties carry it. Where a 4 in tie was too short to wrap pipe plus servo body, two were daisy-chained (tail of one fed through the head of the next) to make a longer strap.

## Practical Reliability Notes

- Tie down wires before adding clothing.
- Keep both syringes and the tubing run visible enough that judges can inspect how the pointing arm moves. Visibility of the fluid power system is directly scored.
- Store the syringes with the plunger left partway inside, not fully withdrawn, so the rubber seals do not dry out.
- Never put soap or oil in the water. It strips the seal coating and causes stiction.
- Avoid permanent glue on the shell; the reveal is part of the judging flow.
- Use fresh AA and 9V batteries for competition runs.
- Test after transport, not only before packing.
