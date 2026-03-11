---
title: MADS Settings
---

# MADS Settings

Fine-tune how the Modular Assistive Driving System (MADS) engages and disengages steering assistance.

**Location:** Settings → sunnypilot → Steering → MADS Settings

!!! info "Prerequisite"
    The main **MADS** toggle must be enabled in [Steering Settings](steering.md) to access these settings.

---

## Main Cruise Allowed

| Property | Value |
|----------|-------|
| **Param** | `MadsMainCruiseAllowed` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

When enabled, pressing the main cruise button (the on/off button on the steering wheel) can activate MADS steering assistance.

!!! warning "Vehicle Restrictions"
    - **Rivian:** Always forced OFF (limited settings mode)
    - **Tesla (without vehicle bus):** Always forced OFF (limited settings mode)

---

## Unified Engagement Mode

| Property | Value |
|----------|-------|
| **Param** | `MadsUnifiedEngagementMode` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

When enabled, engaging cruise control also automatically engages MADS lateral control in a single action, rather than requiring separate activation.

!!! warning "Vehicle Restrictions"
    - **Rivian:** Always forced ON (limited settings mode)
    - **Tesla (without vehicle bus):** Always forced ON (limited settings mode)

---

## Steering Mode on Disengage

| Property | Value |
|----------|-------|
| **Param** | `MadsSteeringMode` |
| **Type** | Multi-button selector |
| **Options** | Remain Active · Pause · Disengage |
| **Default** | Remain Active |

Controls what happens to MADS steering assistance when you disengage cruise control:

| Mode | Behavior |
|------|----------|
| **Remain Active** | Steering assistance continues even after cruise is disengaged |
| **Pause** | Steering assistance pauses but can be quickly resumed |
| **Disengage** | Steering assistance fully disengages with cruise |

!!! warning "Vehicle Restrictions"
    - **Rivian:** Always forced to Disengage (limited settings mode)
    - **Tesla (without vehicle bus):** Always forced to Disengage (limited settings mode)

---

## Related Features

- [Modular Assistive Driving System](../features/mads.md)
