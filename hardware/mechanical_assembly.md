# Mechanical Assembly - "The North Star"

This document describes the supported mechanical build: a PVC-and-wood skeleton on a plywood base, with exposed electronics, servo-driven head motion, a syringe-driven right arm, and a removable outer presentation layer.

## Base and Skeleton

- **Base:** Plywood platform holding the Arduino/breadboard control stack, DFPlayer, PIR sensor, speaker, 9V battery, and switched 4xAA servo battery pack.
- **Spine:** A vertical 1/2 in PVC support rises from the base and carries the upper body.
- **Shoulders:** A PVC tee and horizontal shoulder pipe form the upper frame.
- **Head:** A painted foam head sits on a vertical dowel driven by the head servo at the top of the PVC frame.
- **Removable shell:** Fabric/clothing/backdrop elements sit over or around the skeleton but can be removed for judging.

## Motion Assemblies

### Head Turn

An MG996R servo mounted near the top of the PVC frame turns the foam head through a vertical dowel. This provides a clear "comes to life" motion without needing a complex jaw.

### Syringe-Driven Right Arm

The right-side gesture arm is driven by a visible syringe linkage:

- A large 60 mL syringe is mounted horizontally on the right side of the frame.
- An MG996R servo on the base drives the syringe through a short wooden linkage.
- The syringe linkage connects to the right-side arm mechanism.
- The arm pivots on a plain metal pin through a drilled hole at the shoulder. The hole is slightly larger than the pin diameter so the arm swings freely without binding, while remaining constrained to a single axis of rotation. No powered servo is used at the hinge.
- Linkage alignment matters more than force. If the plunger or arm is pushed sideways, it binds and wastes servo torque.

### Lantern Arm

An SG90 servo mounted on the left shoulder area raises the wood-stick lantern assembly. The warm white lantern LED is controlled separately by the Arduino so the light can turn on before or during the arm movement.

## Practical Reliability Notes

- Tie down wires before adding clothing.
- Keep the syringe mechanism visible enough that judges can inspect how the right arm moves.
- Avoid permanent glue on the shell; the reveal is part of the judging flow.
- Use fresh AA and 9V batteries for competition runs.
- Test after transport, not only before packing.
