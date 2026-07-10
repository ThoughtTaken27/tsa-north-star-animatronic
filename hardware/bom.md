# Bill of Materials and Pin Map - "The North Star"

This file records the supported hardware configuration for the Arduino-controlled animatronic exhibit. The specific part names below were verified from purchase screenshots and store receipts dated March 7, March 13, and March 28, 2026. Raw receipts are not stored in this public repository because they contain order, payment, and contact details.

## Bill of Materials

| Component | Specification / Model | Qty | System Role |
| :--- | :--- | :---: | :--- |
| Arduino-compatible Uno R3 | ELEGOO UNO R3 Board ATmega328P with USB cable | 1 | Main control board |
| MG996R servo | Deegoo-FPV 2-pack MG996R 55 g metal gear digital servo | 2 | Head turn and right-side syringe linkage |
| SG90 servo | Dorhea 5-pack SG90 9 g micro servo kit | 1 used, spares retained | Lantern arm movement and backup parts |
| DFPlayer Mini | DFPlayer Mini MP3 player module | 1 used, spare retained | Narration playback |
| microSD card | Patriot LX 16 GB microSD card with adapter, UHS-I C10 A1 | 1 used | Audio storage |
| Speaker | 3 W, 8 ohm mini loudspeaker with JST-PH2.0 lead | 1 | Audio output |
| HC-SR501 PIR sensor | HiLetgo HC-SR501 PIR infrared motion sensor module pack | 1 used, spares retained | Viewer trigger |
| LEDs | Chanzon 5 mm warm white LEDs plus a separate North Star LED from project build materials | 2+ | Lantern and North Star lighting |
| LED resistors | 220 ohm resistors from Chanzon 60-value 1/4 W resistor kit | 2+ | LED current limiting |
| DFPlayer divider resistors | 680 ohm and 1k ohm resistors from Chanzon resistor kit | 1 each | Drops Arduino TX to DFPlayer RX-safe logic level |
| Capacitor | FymuSing 1000 uF 25V aluminum electrolytic capacitor pack | 1 used, spares retained | Buffers servo rail voltage dips |
| Syringe | 60 mL plastic liquid syringe with tip cap | 1 visible in final build, spares retained | Right-side arm linkage |
| Syringe linkage materials | Wood linkage, tape, zip ties, and mounting hardware | As needed | Transfers servo motion into the syringe plunger |
| Jumper wires | 120-piece multicolored Dupont jumper wire kit | As needed | Breadboard wiring |
| Cable ties | 4 in black nylon cable ties | As needed | Wire and frame management |
| Servo power | LampVPath 4xAA battery holder with switch | 1 | Separate 6V nominal servo rail |
| Logic power | 9V battery clip to 2.1 mm x 5.5 mm barrel plug adapter | 1 | Arduino input power |
| Frame materials | 1/2 in PVC pipe/fittings, foam ball, wood sticks/dowels, craft/fabric items | As needed | Exhibit body and removable shell |

## Documented Cost Summary

The available receipts document at least **$183.63** in project purchases:

| Source | Date | Documented Total |
| :--- | :--- | ---: |
| Main Amazon electronics/materials order | March 7, 2026 | $140.95 |
| Amazon microSD card order | March 7, 2026 | $10.96 |
| Amazon speaker order | March 7, 2026 | $5.48 |
| Home Depot PVC/fittings receipt | March 13, 2026 | $6.45 |
| Walmart craft/materials receipt | March 28, 2026 | $19.79 |
| **Documented subtotal** |  | **$183.63** |

This is a documented subtotal, not a guaranteed full project cost. It excludes any reused tools, already-owned supplies, or unrecorded consumables.

## Store-Receipt Material Details

The Home Depot receipt verifies the PVC frame materials used for the skeleton:

- 1/2 in PVC pipe.
- 1/2 in PVC coupling.
- 1/2 in PVC 90-degree elbow.
- 1/2 in PVC tee.

The Walmart receipt verifies visible craft/display materials used for the outer presentation:

- Foam ball.
- Wood stick pack.
- Craft/fabric items used for the figure, clothing, and display finish.

## Pin Mapping

| Arduino Pin | Connected Component | Signal Type | Notes |
| :---: | :--- | :--- | :--- |
| `D2` | DFPlayer Mini TX | SoftwareSerial RX | Direct signal from DFPlayer to Arduino |
| `D3` | DFPlayer Mini RX | SoftwareSerial TX | Route through 680 ohm / 1k ohm voltage divider |
| `D4` | North Star LED | Digital output | LED anode through 220 ohm resistor, cathode to ground |
| `D5` | Lantern LED | Digital output | LED anode through 220 ohm resistor, cathode to ground |
| `D6` | MG996R syringe-drive servo | Servo signal | Moves the right arm linkage |
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

The Arduino TX signal on `D3` is 5V logic. The DFPlayer Mini RX input is commonly treated as 3.3V logic, so the project used a simple divider:

```text
Arduino D3 ---- 680 ohm ----+---- DFPlayer RX
                            |
                           1k ohm
                            |
                           GND
```

That gives roughly 3V at the DFPlayer RX node from a 5V Arduino output.
