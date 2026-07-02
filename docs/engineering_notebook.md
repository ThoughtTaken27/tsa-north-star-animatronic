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
- Planned for movement, sound, light, sensor input, Arduino control, removable shell, and an inspectable syringe mechanism.

### Electronics Prototype

- Set up the Arduino Uno-compatible board.
- Tested servo basics and breadboard wiring.
- Planned separate Arduino logic power and servo power to reduce resets.
- Added a 1000 uF capacitor across the servo rail.

### Mechanical Prototype

- Built a PVC/wood skeleton on a plywood base with a removable outer presentation layer.
- Mounted the head turn servo at the top of the PVC frame, the lantern arm servo on the left shoulder, and the syringe-drive servo near the right-side arm linkage.
- Built the visible syringe linkage used for the right-side gesture arm.

### Integration and Debugging

- Adjusted the syringe mount and linkage geometry so the right arm moved through a cleaner path.
- Secured exposed wiring and servo leads to survive the removable-shell reveal.
- Tuned PIR sensitivity and added a mandatory warm-up period.
- Fixed DFPlayer SD-card format and file naming issues.
- Practiced the reveal and sequence timing before competition.

### Competition

- The project ran as a self-contained battery-powered exhibit with no laptop required during the presentation.
- Judge feedback specifically called out the self-reliant setup and clean circuitry.
- The team placed 1st at the Tennessee TSA State Championship.
