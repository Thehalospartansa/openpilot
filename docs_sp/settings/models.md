---
title: Models & AI Settings
---

# Models & AI Settings

Configure driving model behavior and advanced AI parameters.

**Location:** Settings → sunnypilot → Models & AI

---

## Model Selection

Select which driving model to use. Different models may have different driving characteristics and capabilities.

!!! warning "Offroad Only"
    Model selection can only be changed while the vehicle is offroad (parked with ignition off).

---

## Lane Turn Desire

| Property | Value |
|----------|-------|
| **Param** | `LaneTurnDesire` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables lane-aware turn desire signals to the driving model. When active, the model receives enhanced lane positioning cues during turns.

### Lane Turn Value

| Property | Value |
|----------|-------|
| **Param** | `LaneTurnValue` |
| **Type** | Option selector |
| **Range** | 500–2000 (displayed with float scaling) |
| **Default** | 500 |

Adjusts the intensity of the lane turn desire signal sent to the model. Higher values produce a stronger turn desire.

!!! info "Requirements"
    - Lane Turn Desire must be enabled
    - Advanced Controls must be enabled (`ShowAdvancedControls`)

---

## LAGD (Look-Ahead Generative Driving)

| Property | Value |
|----------|-------|
| **Param** | `LagdToggle` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables the Look-Ahead Generative Driving feature, which uses generative AI to anticipate road conditions ahead.

### LAGD Delay

| Property | Value |
|----------|-------|
| **Param** | `LagdToggleDelay` |
| **Type** | Option selector |
| **Range** | 5–50 (displayed with float scaling) |
| **Default** | 5 |

Configures the look-ahead delay for LAGD. Higher values make the system look further ahead.

!!! info "Requirements"
    - LAGD must be **disabled** (this setting is shown when LAGD is off to configure its parameters before enabling)
    - Advanced Controls must be enabled (`ShowAdvancedControls`)

---

## Related Features

- [Models & AI](../features/models.md)
