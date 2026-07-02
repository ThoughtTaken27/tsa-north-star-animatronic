# Bill of Materials and Pin Map - "The North Star"

This file records the supported hardware configuration for the Arduino-controlled animatronic exhibit.

## Bill of Materials

| Component | Specification / Model | Qty | System Role |
| :--- | :--- | :---: | :--- |
| Arduino-compatible Uno R3 | ATmega328P board | 1 | Main control board |
| MG996R servo | 180-degree metal gear servo | 2 | Head turn and controller syringe drive |
| SG90 servo | 9 g micro servo | 1 | Lantern arm movement |
| DFPlayer Mini | microSD MP3 player module | 1 | Narration playback |
| microSD card | FAT32, `/mp3/0001_harriet.mp3` | 1 | Audio storage |
| HC-SR501 PIR sensor | 3-pin PIR motion sensor | 1 | Viewer trigger |
| Speaker | 8 ohm, 3 W passive speaker | 1 | Audio output |
| LEDs | Warm white and orange/amber 5 mm LEDs | 2+ | Lantern and North Star lighting |
| LED resistors | 220 ohm | 2+ | LED current limiting |
| DFPlayer divider resistors | 680 ohm and 1k ohm | 1 each | Drops Arduino TX to DFPlayer RX-safe logic level |
| Capacitor | 1000 uF electrolytic, 16V+ | 1 | Buffers servo rail voltage dips |
| Syringes | 60 mL slip-tip syringes | 2 | Controller and actuator cylinders |
| Tubing | 3/16 in clear vinyl tubing | As needed | Fluid transfer line |
| Fluid | Blue-tinted water | As needed | Visual fluid power medium |
| Servo power | 4xAA battery holder with switch | 1 | Separate 6V nominal servo rail |
| Logic power | 9V battery with barrel jack adapter | 1 | Arduino input power |
| Frame materials | Plywood, PVC, dowels, zip ties, foam, fabric | As needed | Exhibit body and removable shell |

## Pin Mapping

| Arduino Pin | Connected Component | Signal Type | Notes |
| :---: | :--- | :--- | :--- |
| `D2` | DFPlayer Mini RX | SoftwareSerial TX | Route through 680 ohm / 1k ohm voltage divider |
| `D3` | DFPlayer Mini TX | SoftwareSerial RX | Direct signal to Arduino |
| `D4` | North Star LED | Digital output | LED anode through 220 ohm resistor, cathode to ground |
| `D5` | Lantern LED | Digital output | LED anode through 220 ohm resistor, cathode to ground |
| `D6` | MG996R hydraulic servo | Servo signal | Pushes controller syringe linkage |
| `D7` | HC-SR501 OUT | Digital input | Motion trigger |
| `D9` | MG996R head servo | Servo signal | Turns figure head |
| `D11` | SG90 lantern arm servo | Servo signal | Raises lantern arm |

## Power Layout

- The Arduino is powered through the barrel jack from a 9V battery.
- The servos are powered from a separate 4xAA battery pack, giving a nominal 6V servo rail.
- Arduino ground and servo battery ground are tied together at one common ground rail.
- Servo V+ does not connect to the Arduino 5V pin.
- A 1000 uF electrolytic capacitor is placed across the servo power rail, with polarity checked before power-on.
- The PIR sensor, DFPlayer, and LEDs use the Arduino 5V / ground rails.

## DFPlayer Wiring Note

The Arduino TX signal on `D2` is 5V logic. The DFPlayer Mini RX input is commonly treated as 3.3V logic, so the project used a simple divider:

```text
Arduino D2 ---- 680 ohm ----+---- DFPlayer RX
                            |
                           1k ohm
                            |
                           GND
```

That gives roughly 3V at the DFPlayer RX node from a 5V Arduino output.
