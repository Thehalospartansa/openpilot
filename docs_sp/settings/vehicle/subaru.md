---
title: Subaru Settings
---

# Subaru Vehicle Settings

Settings specific to Subaru vehicles. These settings only appear when a Subaru vehicle is connected.

**Location:** Settings → sunnypilot → Vehicle

---

## Stop and Go (Beta)

| Property | Value |
|----------|-------|
| **Param** | `SubaruStopAndGo` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables auto-resume during stop-and-go traffic for certain supported Subaru platforms. Without this, you must manually resume after a full stop.

!!! info "Requirements"
    - Device must be offroad to toggle
    - Vehicle platform must support Stop and Go (not available on Global Gen2 or Hybrid platforms)

---

## Stop and Go for Manual Parking Brake (Beta)

| Property | Value |
|----------|-------|
| **Param** | `SubaruStopAndGoManualParkingBrake` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables stop-and-go for Subaru Global models equipped with a **manual handbrake** (lever-type parking brake).

!!! warning "Important"
    Models with an **electric parking brake** should keep this **disabled**. This setting is specifically designed for vehicles with a manual/lever parking brake.

!!! info "Requirements"
    - Device must be offroad to toggle
    - Vehicle platform must support Stop and Go (not available on Global Gen2 or Hybrid platforms)

!!! note "Credits"
    Thanks to martinl for this implementation.

---

## Platform Compatibility

Both Stop and Go features are **not available** on:

- Subaru Global Gen2 platforms
- Subaru Hybrid platforms

If your vehicle falls into these categories, the toggles will be hidden or disabled with the message: "This feature is currently not available on this platform."

If the vehicle is onroad, you'll see: "Enable 'Always Offroad' in Device panel, or turn vehicle off to toggle."
