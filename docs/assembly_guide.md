# Assembly and Calibration Guide - "The North Star"

This guide covers the practical build sequence for the final exhibit configuration: a portable waist-up animatronic with a PVC skeleton, exposed Arduino control base, servo motion, LEDs, audio, PIR trigger, and a syringe-driven right arm.

## Frame Setup

1. Mount the central support to the plywood base.
2. Attach the PVC spine and shoulder structure.
3. Mount the head servo at the top of the PVC frame and attach the foam head through a vertical dowel.
4. Mount the left SG90 servo at the shoulder area for the lantern arm.
5. Mount the right-side syringe and MG996R drive linkage so the plunger moves cleanly. The right arm pivots on a plain metal pin through a drilled hole at the shoulder — no powered servo at the hinge.
6. Keep the Arduino, breadboard, batteries, speaker, and DFPlayer accessible on the base for testing and judge inspection.
7. Route wires along the frame and tie them down before adding the outer shell.
8. Keep the shell removable. The internal skeleton, wiring, and syringe linkage need to be visible during judging.

## Syringe Linkage

The right arm uses a 60 mL syringe driven by an MG996R servo linkage:

```text
 [MG996R servo] -> [wood linkage] -> [60 mL syringe] -> [right arm linkage]
```

Setup notes:

1. Mount the syringe body firmly so it cannot twist when the servo pushes.
2. Align the servo horn and wooden linkage so the syringe plunger is pushed straight along its axis.
3. Add pivot freedom where needed so the arm can move through its arc without forcing the syringe sideways.
4. Test repeatedly before adding clothing, because the fabric can hide binding and linkage problems.

## Servo Calibration

Never drive hobby servos to full `0` to `180` degree travel in the final build. Start from conservative software limits and widen only after checking that the physical mechanism does not bind.

| Assembly | Servo | Pin | Home | Approx. Active Range | Purpose |
| :--- | :--- | :---: | :---: | :---: | :--- |
| Head turn | MG996R | `D9` | 90 deg | 55-125 deg | Turns figure toward viewer/backdrop |
| Syringe drive | MG996R | `D6` | 45 deg | 40-130 deg | Moves the right arm linkage |
| Lantern arm | SG90 | `D11` | 70 deg | 60-125 deg | Raises lantern arm |

Calibration protocol:

1. Upload a simple servo-centering sketch or use the main firmware home positions.
2. Attach horns and dowels only after the servo is at its intended home angle.
3. Sweep slowly in 5-degree increments.
4. Stop immediately if a servo buzzes, stalls, heats quickly, or the Arduino resets.
5. Reduce the software limit rather than forcing the mechanism.

## Competition Startup

1. Turn on the Arduino and servo power during setup.
2. Wait through the 60-second PIR warm-up window.
3. Confirm the DFPlayer has the SD card inserted.
4. Trigger once by walking in front of the PIR.
5. Let the full sequence finish before resetting or moving the exhibit.
