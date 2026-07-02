# Mechanical Assembly - "The North Star"

This document describes the supported mechanical build: a PVC/wood student-built skeleton with servo-driven head motion, a syringe-powered gesture arm, and a removable outer shell.

## Base and Skeleton

- **Base:** Plywood platform holding the Arduino, breadboard, batteries, speaker, PIR sensor, and visible wiring.
- **Spine:** PVC vertical support mounted near the center of the base.
- **Shoulders:** Short PVC shoulder pieces create mounting points for the lantern arm and hydraulic arm.
- **Removable shell:** Foam, fabric, clothing, and backdrop elements sit over the skeleton but can be removed for judging.

## Motion Assemblies

### Head Turn

An MG996R servo turns the head through a dowel or neck post. This provides a clear "comes to life" motion without needing a complex jaw.

### Hydraulic Arm

The fluid-power system raises the gesture arm:

- A controller syringe is pushed by an MG996R servo.
- A 3/16 in vinyl tube carries blue-tinted water to a second syringe.
- The actuator syringe pushes a dowel arm around a shoulder pivot.
- Linkage alignment matters more than force. If the plunger is pushed sideways, it binds and wastes servo torque.

### Lantern Arm

An SG90 servo raises the lantern arm. The warm white lantern LED is controlled separately by the Arduino so the light can turn on before or during the arm movement.

## Practical Reliability Notes

- Tie down wires before adding clothing.
- Keep tubing visible enough that the fluid-power requirement is obvious during the reveal.
- Avoid permanent glue on the shell; the reveal is part of the judging flow.
- Use fresh AA and 9V batteries for competition runs.
- Test after transport, not only before packing.
