import os
import re

print("======================================================================")
print("RUNNING REPOSITORY PATH & INTEGRITY VERIFICATION SCRIPT")
print("======================================================================")

base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
print(f"Target Base Directory: {base_dir}")

required_files = [
    "README.md",
    ".gitignore",
    "LICENSE",
    "hardware/bom.md",
    "hardware/schematics/system_schematic_ascii.txt",
    "docs/assembly_guide.md",
    "docs/postmortem_failure_log.md",
    "docs/publishing_guide.md",
    "docs/historical_context.md",
    "docs/engineering_notebook.md",
    "hardware/mechanical_assembly.md",
    "tsa-north-star-animatronic.ino",
    "src/Sensors.h",
    "src/Sensors.cpp",
    "src/Actuators.h",
    "src/Actuators.cpp",
    "src/AudioController.h",
    "src/AudioController.cpp",
    "src/StateEngine.h",
    "src/StateEngine.cpp"
]

all_passed = True

print("\n--- Phase 1: Verifying File Presence & Sizes ---")
for f in required_files:
    full_path = os.path.join(base_dir, f)
    if os.path.exists(full_path):
        size_bytes = os.path.getsize(full_path)
        with open(full_path, "r", encoding="utf-8") as file_obj:
            lines = len(file_obj.readlines())
        print(f"OK FOUND: {f:<50} | Lines: {lines:<5} | Size: {size_bytes:<5} bytes")
    else:
        print(f"FAIL MISSING: {f}")
        all_passed = False

print("\n--- Phase 2: Verifying Markdown Link Integrity ---")
md_files = [f for f in required_files if f.endswith(".md")]
for md in md_files:
    full_path = os.path.join(base_dir, md)
    print(f"\nChecking links inside: {md}")
    with open(full_path, "r", encoding="utf-8") as file_obj:
        content = file_obj.read()
    content = re.sub(r"```.*?```", "", content, flags=re.DOTALL)
    
    # Simple regex to extract local relative links like [Text](./path) or [Text](path)
    links = re.findall(r'\[.*?\]\((.*?)\)', content)
    for link in links:
        # Filter out external http links or absolute URLs
        if link.startswith("http") or link.startswith("#"):
            continue
        
        # Clean query or hash parts
        link_cleaned = link.split("#")[0].split("?")[0]
        if not link_cleaned:
            continue
            
        # Resolve path relative to markdown file parent dir
        md_dir = os.path.dirname(full_path)
        linked_path = os.path.normpath(os.path.join(md_dir, link_cleaned))
        
        if os.path.exists(linked_path):
            print(f"  OK Link Valid: '{link}' -> resolved to local file")
        else:
            print(f"  FAIL Broken Link: '{link}' -> resolved to missing path '{linked_path}'")
            all_passed = False

print("\n======================================================================")
if all_passed:
    print("VERIFICATION RESULT: ALL TESTS PASSED. REPOSITORY IS PRISTINE & VALID.")
else:
    print("VERIFICATION RESULT: INTEGRITY CHECK FAILED. FIX MISSING FILES OR LINKS.")
print("======================================================================")
