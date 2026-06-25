# GitHub Publishing Guide — "The North Star"

Steps for publishing the repository and managing visibility.

---

## Step 1: Initialize the Local Git Repository

When managing your files, never use general catch-all commands like `git add .`. This can result in pushing temporary IDE files, build artifacts, or secret keys to a public space. Add your files individually.

Execute the following commands in your terminal:

```bash
# Navigate to the repository root directory
cd /Users/parthkhavate/Downloads/Second\ brain-opencode/tsa-north-star-animatronic/

# Initialize a clean Git repository
git init

# Verify that the .gitignore file is present
cat .gitignore

# Stage the configuration and core documentation files individually
git add .gitignore
git add README.md

# Stage the hardware directories
git add hardware/bom.md
git add hardware/schematics/system_schematic_ascii.txt

# Stage the technical documentation files
git add docs/assembly_guide.md
git add docs/postmortem_failure_log.md

# Stage the firmware source files individually
git add tsa-north-star-animatronic.ino
git add src/Sensors.h
git add src/Sensors.cpp
git add src/Actuators.h
git add src/Actuators.cpp
git add src/AudioController.h
git add src/AudioController.cpp
git add src/StateEngine.h
git add src/StateEngine.cpp

# Verify staged files (ensure no build files or DS_Store are listed)
git status

# Commit the files with a professional, descriptive commit message
git commit -m "Initial commit: Core firmware, schematics, and postmortem documentation for Tennessee State Championship animatronic"
```

---

## Step 2: Establish the Public Repository on GitHub

1.  Log in to [GitHub.com](https://github.com/).
2.  Click **New** to create a new repository.
3.  Configure the repository settings exactly as follows:
    *   **Repository Name:** `tsa-north-star-animatronic`
    *   **Description:** `Tennessee TSA State Championship animatronic bust — battery-powered servos, hydraulic syringe actuators, and asynchronous firmware control.`
    *   **Public/Private:** Set to **Public**.
    *   **Initialize repository with:** Leave all checkboxes (README, .gitignore, License) **unchecked** (since we have already authored these files locally).
4.  Click **Create repository**.
5.  Link your local repository to the new remote and push the master branch:

```bash
# Add the remote origin link (replace with your GitHub username)
git remote add origin https://github.com/Parthkkk/tsa-north-star-animatronic.git

# Set branch name to main
git branch -M main

# Push the committed code to the remote server
git push -u origin main
```

---

## Step 3: Capture & Host High-Impact Visual Assets

A visual at the top of the README helps demonstrate the project is functional.

### 1. Capture Guidelines
*   **Duration:** Keep videos under 15 seconds.
*   **Angle 1:** Wide shot showing the PIR sensor triggering the animatronic, head panning, jaw movement, and hydraulic neck lift.
*   **Angle 2 (The Mechanics):** Tight shot of the MG996R servo driving the custom master syringes and the blue liquid flowing smoothly through the clear PVC tubing.
*   **Angle 3 (The Electronics):** A clean shot of the breadboard showing the 4×AA battery pack, common ground point, and 1000µF capacitor.

### 2. Asset Hosting Protocol
*   **Option A (Embedded GIF - Recommended):** Convert your raw video file to a high-quality, compressed `.gif` (under 5MB to ensure fast loading times) using `ffmpeg` or an online converter.
    *   Save the file as `docs/assets/demo_hook.gif`.
    *   Add and commit the file individually: `git add docs/assets/demo_hook.gif`.
    *   Embed the GIF at the top of your `README.md` by replacing the visual placeholder with:
        ```markdown
        ![The North Star Demo](./assets/demo_hook.gif)
        ```
*   **Option B (YouTube Embed fallback):** Upload the high-quality 15-second clip to YouTube as an "Unlisted" video (to keep it clean) and link it in the README with a high-resolution thumbnail preview.

---

## Step 4: Optimize Metadata & Repository Discovery

To make your repository look like a professional, industry-grade project:

1.  **Add Topics (Tags):** Click the gear icon next to "About" on the right side of your GitHub repository page and enter these exact topics:
    *   `arduino`, `embedded-systems`, `finite-state-machine`, `robotics`, `animatronics`, `hydraulics`, `c-plus-plus`, `hardware-portfolio`, `systems-integration`.
2.  **Verify Link Integrity:** Click through every single link in your published `README.md` and verification files. Ensure there are no broken links, spelling errors, or stale file pathways.

---

## Step 5: Incorporate the Repository into Your Applications

Once the repository is live, integrate it across your application touchpoints to maximize impact.

### 1. Common Application (Activities Section)
*   **Activity Type:** Science/Technology
*   **Position/Leadership:** Team Captain & Systems Integrator (TSA Animatronics Team)
*   **Description (150 Character Limit):**
    `Designed TSA state championship animatronic. Battery-powered servos, hydraulic syringe actuators, asynchronous C++ firmware.`
*   **Web Link:** Since the Common App activities section does not allow hyperlinks, place your short GitHub URL directly at the end of the description if character limits allow, or include it in your main resume file.

### 2. Portfolio Uploads (SlideRoom / Engineering Portals)
*   For engineering program submissions, upload a PDF of the [**Postmortem Failure Log**](./postmortem_failure_log.md) or link the repository URL.

### 3. Professional LinkedIn Post (Optional)
*   Post a 10-second video of "The North Star" performing its sequence.
*   **Sample Copy:**
    `Complete technical docs and source for "The North Star" — Tennessee TSA State Championship animatronic bust. Battery-powered servos, hydraulic syringe actuators, non-blocking C++ firmware. Full schematics and debugging log: [Link]`
