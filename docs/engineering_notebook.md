# Engineering Notebook - "The North Star"

This notebook summarizes the build timeline, team structure, and major technical decisions for the TSA Animatronics project.

## Team Structure

- **Parth Khavate - Team Captain / Systems Integrator:** Arduino programming, wiring, DFPlayer setup, servo integration, troubleshooting, documentation, and final technical decisions.
- **Mechanical Lead:** PVC/wood frame, servo mounting, syringe linkage, and physical construction.
- **Creative Lead:** Head, clothing, backdrop, narration, and museum-style presentation.

## Build Timeline

### Concept and Planning

- Chose Harriet Tubman and "The North Star" as the exhibit theme.
- Designed the project around a children's museum interaction: approach, trigger, narration, motion, lighting, reset.
- Planned for minimum required movement, sound, light, sensor, control technology, removable shell, and fluid power.

### Electronics Prototype

- Set up the Arduino Uno-compatible board.
- Tested servo basics and breadboard wiring.
- Planned separate Arduino logic power and servo power to reduce resets.
- Added a 1000 uF capacitor across the servo rail.

### Mechanical Prototype

- Built a PVC/wood skeleton with a removable outer presentation layer.
- Mounted the head turn servo, lantern arm servo, and syringe-drive servo.
- Built the two-syringe fluid-power mechanism with clear tubing and blue-tinted water.

### Integration and Debugging

- Fixed tubing fit and air bubble problems in the syringe line.
- Adjusted linkage geometry so the hydraulic arm moved through a cleaner path.
- Tuned PIR sensitivity and added a mandatory warm-up period.
- Fixed DFPlayer SD-card format and file naming issues.
- Practiced the reveal and sequence timing before competition.

### Competition

- The project ran as a self-contained battery-powered exhibit with no laptop required during the presentation.
- Judge feedback specifically called out the self-reliant setup and clean circuitry.
- The team placed 1st at the Tennessee TSA State Championship.
