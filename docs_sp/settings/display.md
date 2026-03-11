---
title: Display Settings
---

# Display Settings

Control screen brightness, timeout, and interactivity behavior while driving.

**Location:** Settings → sunnypilot → Display

---

## Onroad Screen Off Brightness

| Property | Value |
|----------|-------|
| **Param** | `OnroadScreenOffBrightness` |
| **Type** | Option selector |
| **Range** | 0–22 |
| **Default** | 0 (Auto) |

Controls the screen brightness level when the display times out during driving.

| Value | Label | Behavior |
|-------|-------|----------|
| 0 | Auto | Adjusts brightness automatically based on ambient conditions |
| 1 | Auto Dark | Same as Auto, but dims more aggressively |
| 2 | Screen Off | Turns the screen completely off |
| 3–22 | 5%–100% | Fixed brightness percentage (increments of 5%) |

---

## Onroad Brightness Delay

| Property | Value |
|----------|-------|
| **Param** | `OnroadScreenOffTimer` |
| **Type** | Option selector |
| **Range** | 0–15 |
| **Default** | 0 |

Sets how long the screen stays at full brightness before dimming to the "Screen Off Brightness" level. The values map to specific time durations.

!!! info "Requirements"
    - This setting is disabled when **Onroad Screen Off Brightness** is set to Auto or Auto Dark (values 0 or 1), since those modes manage brightness continuously

---

## Interactivity Timeout

| Property | Value |
|----------|-------|
| **Param** | `InteractivityTimeout` |
| **Type** | Option selector |
| **Range** | 0–120 seconds (step: 10) |
| **Default** | 0 (disabled) |

Sets how long the screen remains interactive after the last touch. After this timeout, the screen becomes non-interactive (touch inputs are ignored) until you tap to wake it.

- **0:** Disabled — screen always remains interactive
- **10–120:** Screen becomes non-interactive after the specified number of seconds

---

## Related Features

- [Onroad Display](../features/onroad-display.md)
