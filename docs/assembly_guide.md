# Assembly and Calibration Guide - "The North Star"

This guide covers the practical build sequence for the final exhibit configuration: a portable waist-up animatronic with a PVC skeleton, exposed Arduino control base, servo motion, LEDs, audio, PIR trigger, and a syringe-driven right arm.

## Frame Setup

1. Mount the central support to the plywood base.
2. Attach the PVC spine and shoulder structure.
3. Mount the head servo at the top of the PVC frame and attach the foam head through a vertical dowel.
4. Zip-tie the SG90 servo to the end of the shoulder crossbar for the lantern arm. Hot glue positions it; the zip ties carry the load.
5. Mount the drive syringe and MG996R linkage on top of the base so the plunger moves cleanly, and mount the output syringe at the shoulder. The right arm pivots on a plain metal pin through a drilled hole at the shoulder — no powered servo at the hinge, all force comes from the fluid column.
6. Keep the Arduino, breadboard, batteries, speaker, and DFPlayer accessible on the base for testing and judge inspection.
7. Route wires along the frame and tie them down before adding the outer shell.
8. Keep the shell removable. The internal skeleton, wiring, and syringe linkage need to be visible during judging.

## Fluid Power Circuit

The pointing arm is driven by a closed two-syringe water circuit:

```text
 [MG996R servo] -> [wooden dowel linkage] -> [60 mL DRIVE syringe, on base]
        |
        v
 [3/16 in ID clear vinyl tubing, up the spine]
        |
        v
 [60 mL OUTPUT syringe, at shoulder] -> [dowel link] -> [pointing arm]
```

Setup notes:

1. Mount both syringe bodies firmly so neither can twist when the servo pushes.
2. Align the servo horn and wooden dowel linkage so the drive plunger is pushed straight along its axis.
3. Add pivot freedom where needed so the arm can move through its arc without forcing the output syringe sideways.
4. Test repeatedly before adding clothing, because the fabric can hide binding and linkage problems.

### Filling procedure (order matters)

Do not connect both syringes and then fill — that seals air into the second syringe with no exit path, and trapped air compresses instead of transferring force.

1. Fill one syringe completely with clean water. No soap, no oil, no additives; they strip the seal coating and cause stiction.
2. Attach the tubing to that syringe only. Leave the far end of the tube open.
3. Push water through until the open end is running and dripping, so the whole tube is fluid.
4. Attach the second, empty syringe while that end is still wet.

Between sessions, empty the water but leave the plungers partway in rather than fully removed, so the seals do not dry out.

## Servo Calibration

Never drive hobby servos to full `0` to `180` degree travel in the final build. Start from conservative software limits and widen only after checking that the physical mechanism does not bind.

| Assembly | Servo | Pin | Home (Modular FSM) | Home (Competition) | Approx. Active Range | Purpose |
| :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| Head turn | MG996R | `D9` | 90 deg | 90 deg (rest), 60 deg (forward) | 55-125 deg | Turns figure toward viewer/backdrop |
| Syringe drive | MG996R | `D6` | 45 deg | 70 deg (rest), 18 deg (push) | 40-130 deg | Drives the fluid power pointing arm |
| Lantern arm | SG90 | `D11` | 70 deg | 0 deg (down), 90 deg (up) | 60-125 deg | Raises lantern arm |

Note: The "Modular FSM" home values are the safe-angle limits used by `tsa-north-star-animatronic.ino`. The "Competition" values are the actual angles used in `firmware/firmware.ino` — the code that ran at the state championship.

Calibration protocol:

1. Upload a simple servo-centering sketch or use the main firmware home positions.
2. Attach horns and dowels only after the servo is at its intended home angle.
3. Sweep slowly in 5-degree increments.
4. Stop immediately if a servo buzzes, stalls, heats quickly, or the Arduino resets.
5. Reduce the software limit rather than forcing the mechanism.

On the syringe drive specifically: push angles were found by testing rather than calculation. 18 degrees was verified good and is what shipped. A later trial at 15 degrees was flagged as a grinding risk because it sits closer to the mechanism's physical stop. If it ever grinds, move *up* (19, 20, 21), never down.

## Competition Startup

1. Turn on the Arduino and servo power during setup.
2. Wait through the 60-second PIR warm-up window.
3. Confirm the DFPlayer has the SD card inserted.
4. Trigger once by walking in front of the PIR.
5. Let the full sequence finish before resetting or moving the exhibit.
