# Power Stability Note — "The North Star"

## The Problem

During early full-sequence testing, the Arduino would reset mid-sequence — usually when the neck yaw servo and the hydraulic syringe servo fired at the same time. Audio cut out, servos twitched, and the sequence restarted.

## Root Cause

The three MG996R servos were initially powered from the Arduino's 5V pin. The Uno's onboard voltage regulator can source roughly 500mA before dropping out. Multiple servos starting from rest simultaneously can draw several amps for a few milliseconds — far exceeding what the regulator can supply. The resulting voltage sag on the 5V rail dropped below the ATmega328P's brownout detection threshold (~4.3V), triggering a hardware reset.

## The Fix (Two Steps)

1. **Moved servo power off the Arduino 5V pin** — connected all three MG996R servos to a dedicated 4×AA battery pack (1.5V × 4 ≈ 6V). The Arduino continued to run from USB power.

2. **Added a 1000µF 25V electrolytic capacitor** across the battery pack's output. This acts as a local charge reservoir — when the servos demand sudden current, the capacitor supplies it immediately rather than letting the voltage sag.

Both grounds (Arduino GND and battery pack GND) were tied together to keep signal references in sync.

## Result

After both changes, the sequence ran 30 consecutive times with zero resets. The fix was verified at competition — the system ran continuously during setup, presentation, and judge evaluation without a single brownout event.