---
title: Torque Settings
---

# Torque Settings

Advanced tuning parameters for torque-based lateral (steering) control. These settings allow fine-grained control over how the steering motor responds.

**Location:** Settings → sunnypilot → Steering → Torque Settings

!!! info "Prerequisite"
    **Enforce Torque Control** must be enabled in [Steering Settings](steering.md) to access these settings. Not available on vehicles with angle-based steering.

!!! warning "Offroad Only"
    All torque settings can only be changed while the vehicle is offroad (parked with ignition off).

---

## Self-Tune (Live Torque)

| Property | Value |
|----------|-------|
| **Param** | `LiveTorqueParamsToggle` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables real-time self-tuning of torque parameters based on driving behavior. The system continuously adjusts lateral acceleration factor and friction values for optimal steering feel.

---

## Relaxed Self-Tune

| Property | Value |
|----------|-------|
| **Param** | `LiveTorqueParamsRelaxedToggle` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Uses a more relaxed (less aggressive) self-tuning profile. May provide a smoother but less responsive steering feel.

!!! info "Requirements"
    - Self-Tune (Live Torque) must be enabled

---

## Custom Tune

| Property | Value |
|----------|-------|
| **Param** | `CustomTorqueParams` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables manual override of torque control parameters. When enabled, you can set specific values for lateral acceleration and friction instead of relying on self-tuning.

---

## Override Enabled

| Property | Value |
|----------|-------|
| **Param** | `TorqueParamsOverrideEnabled` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Master switch for applying your custom torque parameter overrides.

!!! info "Requirements"
    - Custom Tune must be enabled

---

## Lateral Acceleration Factor

| Property | Value |
|----------|-------|
| **Param** | `TorqueParamsOverrideLatAccelFactor` |
| **Type** | Option selector |
| **Range** | 1–500 (displayed as value ÷ 100) |
| **Default** | 100 (displayed as 1.00) |

Controls the lateral acceleration gain. Higher values produce more aggressive steering response; lower values produce softer response.

- Display: The raw value is divided by 100 (e.g., 250 → 2.50)
- Example: A value of 150 means 1.50× lateral acceleration factor

!!! info "Requirements"
    - Custom Tune must be enabled

---

## Friction

| Property | Value |
|----------|-------|
| **Param** | `TorqueParamsOverrideFriction` |
| **Type** | Option selector |
| **Range** | 1–100 (displayed as value ÷ 100) |
| **Default** | 50 (displayed as 0.50) |

Controls the friction compensation factor. Adjusts how much the system compensates for steering friction in the vehicle.

- Display: The raw value is divided by 100 (e.g., 75 → 0.75)

!!! info "Requirements"
    - Custom Tune must be enabled

---

## Torque Control Tune Version

| Property | Value |
|----------|-------|
| **Param** | `TorqueControlTune` |
| **Type** | Version selector |
| **Default** | Latest available |

Select which version of the torque control tuning algorithm to use. Newer versions may offer improved performance but can behave differently than what you're accustomed to.

---

## Related Features

- [Torque Control](../features/torque-control.md)
