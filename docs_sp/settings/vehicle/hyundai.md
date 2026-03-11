---
title: Hyundai Settings
---

# Hyundai / Kia / Genesis Vehicle Settings

Settings specific to Hyundai, Kia, and Genesis vehicles. These settings only appear when a supported vehicle is connected.

**Location:** Settings → sunnypilot → Vehicle

---

## Custom Longitudinal Tuning

| Property | Value |
|----------|-------|
| **Param** | `HyundaiLongitudinalTuning` |
| **Type** | Multi-button selector |
| **Options** | Off · Dynamic · Predictive |
| **Default** | Off (value: 0) |

Selects a longitudinal (speed) control tuning profile optimized for Hyundai/Kia/Genesis vehicles:

| Option | Behavior |
|--------|----------|
| **Off** | Default longitudinal tuning — standard acceleration and braking behavior |
| **Dynamic** | More responsive acceleration and braking for a sportier feel |
| **Predictive** | Smoother, anticipatory speed changes that prioritize comfort |

!!! info "Requirements"
    - sunnypilot Longitudinal Control (Alpha) must be enabled
    - Device must be offroad to change
    - Vehicle platform must support Alpha Longitudinal (not all Hyundai/Kia/Genesis models support this)

!!! note "Platform Compatibility"
    This setting is hidden for vehicles in the `UNSUPPORTED_LONGITUDINAL_CAR` or `CANFD_UNSUPPORTED_LONGITUDINAL_CAR` lists. If you don't see this option, your specific model does not support sunnypilot longitudinal control.

When the setting is unavailable, the description indicates the reason:

- "This feature is unavailable while the car is onroad." — Park and turn off the vehicle first
- "This feature is unavailable because sunnypilot Longitudinal Control (Alpha) is not enabled." — Enable Alpha Longitudinal in openpilot settings
