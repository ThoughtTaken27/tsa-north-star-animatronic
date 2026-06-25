# Fluid Power System: Closed-Loop Hydraulics

This document details the fluid power mechanics, cylinder physics, volume calculations, and seal engineering behind the custom syringe-driven hydraulic neck lift system in "The North Star" animatronic.

---

## 1. System Physics & Piston Displacement

The head tilt mechanism uses a closed-loop master-slave hydraulic cylinder system to achieve smooth, silent linear motion. This design replaces loud mechanical gears with a fluid transmission path.

```text
  [MG996R Servo] ──> (Linkage) ──> [Master Syringe (60ml)]
                                         │
                                   [PVC Tubing] (Clear Fluid Path)
                                         │
  [Neck U-Joint] <── (Linkage) <─── [Slave Syringe (60ml)]
```

### Volume & Area Calculations
The master and slave cylinders use 60ml Luer Lock medical-grade syringes:
- **Piston Inner Diameter ($D$):** 28.5 mm
- **Piston Cross-Sectional Area ($A$):**
  $$A = \pi \left(\frac{D}{2}\right)^2 = \pi \left(\frac{28.5 \times 10^{-3}\,\text{m}}{2}\right)^2 \approx 6.38 \times 10^{-4}\,\text{m}^2$$

### Linear Displacement & Fluid Transfer
The MG996R servo horn provides a rotational sweep of up to 120 degrees, driving the master plunger through a maximum linear travel ($s_{\text{master}}$) of 35mm.

The volume of fluid displaced ($\Delta V$) is:
$$\Delta V = A \times s_{\text{master}} = (6.38 \times 10^{-4}\,\text{m}^2) \times (35 \times 10^{-3}\,\text{m}) \approx 2.23 \times 10^{-5}\,\text{m}^3 \approx 22.3\,\text{ml}$$

In a closed-loop system, this displaced fluid enters the slave cylinder, generating an identical linear travel of 35mm to lift the neck joint:
$$s_{\text{slave}} = \frac{\Delta V}{A} = 35\,\text{mm}$$

---

## 2. Seal Engineering & Friction Control

Standard medical syringes use single-contact rubber plunger seals designed for short-term, low-pressure applications. Under the continuous, high-pressure load of lifting the heavy silicone head assembly, water will bypass the seal.

### Dual O-Ring Retrofit
To establish a pressure-tight dynamic boundary, we retrofitted the master and slave plunger heads:
1.  **Delrin Machining:** Machined custom plunger heads from Delrin rod stock with two precision-grooved gland slots.
2.  **O-Ring Selection:** Fitted the slots with high-performance nitrile rubber (Buna-N) double O-rings (15mm Inner Diameter, 2.5mm width) designed for dynamic liquid seals.
3.  **Lubrication:** Coated the O-rings with high-viscosity silicon grease. This reduces static sliding friction, preventing the servos from stalling or overheating.

---

## 3. Fluid Medium Selection

The choice of fluid is a critical operational constraint:
- **Tap Water (Rejected):** Tap water contains dissolved minerals and organic matter that promote corrosion in metal fittings and cause microbial growth, clouding the tubing lines over time.
- **Air/Pneumatics (Rejected):** Air is a compressible fluid:
  $$PV = nRT$$
  Under load, the air inside the tubes compresses, generating bouncy, jerky, and delayed head movements.
- **Distilled Water-Glycol Mixture (Selected):** We formulated a 20/80 mixture of industrial propylene-glycol and distilled water:
  - **Incompressibility:** Water-glycol is near-incompressible, ensuring instant, synchronized response between the master and slave pistons.
  - **Corrosion/Microbial Inhibitor:** Propylene-glycol prevents bacterial growth, ensuring the lines stay clear.
  - **Lubricity:** The glycol molecules act as a mild lubricant for the PVC tube walls, lowering friction and reducing current load on the MG996R servo motors.
