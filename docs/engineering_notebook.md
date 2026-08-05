# Engineering Notebook - "The North Star"

This notebook summarizes the build timeline, team structure, and major technical decisions for the TSA Animatronics project.

## Team Structure

Three-member team, all first-year TSA competitors, all beginners in electronics, programming, and fluid power at the start of the project.

- **Parth Khavate - Team Captain / Systems Integrator:** component selection and procurement, wiring and electronics architecture, Arduino programming, DFPlayer setup, servo integration, troubleshooting, build scheduling, documentation, and final technical decisions. Code was written with help from a friend rather than solo.
- **Mechanical Lead:** PVC/wood frame, servo mounting, syringe linkage, and physical construction.
- **Creative Lead:** Head, clothing, backdrop, narration script and recording, and museum-style presentation.

Both teammates were competing in other TSA events at the same time, so the majority of the systems and integration work sat with the captain.

## Build Timeline

Dated anchors from receipts and the competition record:

| Date | Event |
| :--- | :--- |
| March 7, 2026 | Main Amazon electronics order placed (three separate orders) |
| March 13, 2026 | Home Depot PVC and fittings |
| March 22, 2026 | Roughly 18 days out from state; core electronics still in verification |
| March 28, 2026 | Walmart craft and display materials; core electronics working, master code mostly done, cosmetics starting, DFPlayer intermittent |
| April 9-12, 2026 | Tennessee TSA State Leadership Conference, Chattanooga Convention Center |
| April 10, 2026 | Evaluation completed. 1st place, 127 / 130 |

### Concept and Planning

- Chose Harriet Tubman and "The North Star" as the exhibit theme.
- Designed the project around a children's museum interaction: approach, trigger, narration, motion, lighting, reset.
- Planned for movement, sound, light, sensor input, Arduino control, removable shell, and an inspectable syringe mechanism.
- Selected the subject partly on mechanical grounds: each of the three required movements had to be historically motivated so it would read without explanation. Head turn = she notices the visitor. Lantern arm = guiding through darkness. Pointing arm = the North Star.
- **Scope cut:** a fourth movement, an articulated jaw, was planned and dropped. Three movements is the competition minimum; three reliable movements were judged worth more than four with one intermittent. Digital pin 10 was left unallocated as a result.

### Electronics Prototype

- Set up the Arduino Uno-compatible board.
- Tested servo basics and breadboard wiring.
- Planned separate Arduino logic power and servo power to reduce resets.
- Added a 1000 uF capacitor across the servo rail.

### Mechanical Prototype

- Built a PVC/wood skeleton on a plywood base with a removable outer presentation layer.
- Mounted the head turn servo at the top of the PVC frame, zip-tied the lantern arm servo to the end of the shoulder crossbar, and mounted the syringe-drive servo flat on the base.
- Built the two-syringe fluid power circuit: drive syringe on the base, vinyl tubing up the spine, output syringe at the shoulder driving the pointing arm through a dowel link.
- Put the whole fluid power assembly on top of the base after the idea of fitting it underneath ran out of clearance. Mounting it on top also made the mechanism inspectable by judges and reachable for debugging.

### Integration and Debugging

- Adjusted the syringe mount and linkage geometry so the right arm moved through a cleaner path.
- Secured exposed wiring and servo leads to survive the removable-shell reveal.
- Tuned PIR sensitivity and jumper mode and added a mandatory 60-second warm-up period. An earlier attempt to establish the unlabeled pinout by trying pin combinations likely damaged the first sensor; a fresh module from the 3-pack was swapped in.
- Fixed DFPlayer SD-card seating, format, and file naming issues, and resolved a separate macOS Arduino IDE library/permissions failure that had been masquerading as an audio problem.
- Rewrote the show timeline around `millis()` so the pointing gesture fires at a fixed offset from audio start rather than drifting with servo sweep durations. The offset was tuned by ear across three revisions: 20 s, then 19 s, then the final 18 s.
- Practiced the reveal and sequence timing before competition.

### Competition

- The project ran as a self-contained battery-powered exhibit with no laptop required during the presentation.
- Judge feedback specifically called out the self-reliant setup and clean circuitry.
- The team placed 1st at the Tennessee TSA State Championship.
