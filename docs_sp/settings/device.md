---
title: Device Settings
---

# Device Settings

Configure device-level behavior including power management, upload settings, and boot options.

**Location:** Settings → sunnypilot → Device

---

## Max Time Offroad

| Property | Value |
|----------|-------|
| **Param** | `MaxTimeOffroad` |
| **Type** | Option selector |
| **Range** | 0–11 |
| **Default** | 0 |

Controls how long the device stays powered on after the vehicle is turned off (offroad). Useful for preserving battery or keeping the device ready for quick starts.

| Value | Duration |
|-------|----------|
| 0 | Immediate shutdown |
| 1 | 5 minutes |
| 2 | 15 minutes |
| 3 | 30 minutes |
| 4 | 1 hour |
| 5 | 2 hours |
| 6 | 3 hours |
| 7 | 6 hours |
| 8 | 12 hours |
| 9 | 24 hours |
| 10 | 48 hours |
| 11 | 30 hours (1800 minutes) |

---

## Device Boot Mode

| Property | Value |
|----------|-------|
| **Param** | `DeviceBootMode` |
| **Type** | Multi-button selector |
| **Options** | Default · Offroad |
| **Default** | Default |

Controls the device's boot behavior:

| Mode | Behavior |
|------|----------|
| **Default** | Normal boot process — device initializes all driving systems on start |
| **Offroad** | Boot into offroad-only mode — useful for configuration and updates without driving |

---

## Quiet Mode

| Property | Value |
|----------|-------|
| **Param** | `QuietMode` |
| **Type** | Dual-button toggle |
| **Default** | Off |

Silences non-critical audible alerts from the device. Safety-critical alerts are never silenced.

---

## Onroad Uploads

| Property | Value |
|----------|-------|
| **Param** | `OnroadUploads` |
| **Type** | Dual-button toggle |
| **Default** | Off |

When enabled, allows the device to upload driving data (logs, video segments) while you're actively driving. When disabled, uploads only occur while parked.

---

## Always Offroad

| Property | Value |
|----------|-------|
| **Param** | `OffroadMode` |
| **Type** | Button |
| **Default** | N/A |

Forces the device into offroad mode, even if the vehicle is running. This is useful for changing settings that require the device to be offroad (like torque tuning or NNLC).

!!! tip
    Some vehicle-specific settings (e.g., Tesla Cooperative Steering, Subaru Stop and Go) require the device to be offroad. Use this button to access those settings without turning off the vehicle.
