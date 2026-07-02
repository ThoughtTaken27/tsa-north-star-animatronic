# Assembly and Calibration Guide - "The North Star"

This guide covers the practical build sequence for the final exhibit configuration: a portable waist-up animatronic with a removable shell, servo motion, LEDs, audio, PIR trigger, and syringe-based fluid power.

## Frame Setup

1. Mount the central support to the plywood base.
2. Attach the PVC spine and shoulder structure.
3. Keep the Arduino, breadboard, batteries, speaker, and DFPlayer accessible on the base for testing and judge inspection.
4. Route wires along the frame and tie them down before adding the outer shell.
5. Keep the shell removable. The internal skeleton, wiring, and fluid system need to be visible during judging.

## Fluid Power Link

The fluid-power motion uses two 60 mL syringes connected by 3/16 in clear vinyl tubing:

```text
 [MG996R servo] -> [controller syringe] == water line == [actuator syringe] -> [arm linkage]
```

Setup notes:

1. Use tubing that fits tightly on the syringe tips. Oversized tubing leaks and slips under load.
2. Fill the line with blue-tinted water so judges can see the fluid path.
3. Remove air bubbles by slow-cycling the system and tapping the tubing.
4. Align the servo horn and linkage so the controller syringe is pushed straight along the plunger axis.
5. Add a pivot or loose cradle where needed so the syringe does not bind as the arm moves through an arc.
6. Test repeatedly before adding clothing, because the fabric can hide leaks and linkage problems.

## Servo Calibration

Never drive hobby servos to full `0` to `180` degree travel in the final build. Start from conservative software limits and widen only after checking that the physical mechanism does not bind.

| Assembly | Servo | Pin | Home | Approx. Active Range | Purpose |
| :--- | :--- | :---: | :---: | :---: | :--- |
| Head turn | MG996R | `D9` | 90 deg | 55-125 deg | Turns figure toward viewer/backdrop |
| Hydraulic drive | MG996R | `D6` | 45 deg | 40-130 deg | Pushes controller syringe |
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
