---
title: Toyota Settings
---

# Toyota / Lexus Vehicle Settings

Settings specific to Toyota and Lexus vehicles. These settings only appear when a Toyota or Lexus vehicle is connected.

**Location:** Settings → sunnypilot → Vehicle

---

## Enforce Factory Longitudinal Control

| Property | Value |
|----------|-------|
| **Param** | `ToyotaEnforceStockLongitudinal` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

When enabled, sunnypilot will **not** take over control of gas and brakes. The factory Toyota/Lexus adaptive cruise control system handles all longitudinal (speed) control.

!!! warning "Side Effects"
    Enabling this will:

    - Disable sunnypilot longitudinal control
    - Disable Alpha Longitudinal if it was enabled
    - Force Stop and Go Hack to Off
    - Trigger an onroad cycle (system restarts driving processes)

!!! info "Requirements"
    - Cannot be changed while the system is engaged (driving)
    - A confirmation dialog is shown before enabling

---

## Stop and Go Hack (Alpha)

| Property | Value |
|----------|-------|
| **Param** | `ToyotaStopAndGoHack` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Allows some Toyota/Lexus cars to automatically resume from a stop during stop-and-go traffic. Without this, you must press the resume button or tap the gas to resume after a full stop.

!!! warning "Alpha Feature"
    This is an alpha feature. Use at your own risk. Only applicable to certain models that support sunnypilot longitudinal control.

!!! info "Requirements"
    - sunnypilot Longitudinal Control must be available and enabled
    - Enforce Factory Longitudinal Control must be **Off**
    - Cannot be changed while the system is engaged (driving)
    - A confirmation dialog is shown before enabling

When requirements are not met, the toggle is disabled and a message indicates what's needed:

- If the vehicle is not connected: "Start the vehicle to check vehicle compatibility."
- If longitudinal control is not available: "sunnypilot Longitudinal Control must be available and enabled for your vehicle to use this feature."
