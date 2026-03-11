---
title: Lane Change Settings
---

# Lane Change Settings

Configure automatic lane change behavior and blind spot monitoring integration.

**Location:** Settings → sunnypilot → Steering → Lane Change Settings

---

## Auto Lane Change Timer

| Property | Value |
|----------|-------|
| **Param** | `AutoLaneChangeTimer` |
| **Type** | Option selector |
| **Options** | Off · Nudge · Nudgeless · 0.5s · 1s · 2s · 3s |
| **Default** | Off (value: -1) |

Controls how lane changes are initiated when the turn signal is activated:

| Option | Value | Behavior |
|--------|-------|----------|
| **Off** | -1 | Auto lane change is disabled |
| **Nudge** | 0 | Requires a light steering nudge in the desired direction to start the lane change |
| **Nudgeless** | 1 | Lane change begins immediately when the turn signal is activated (no nudge needed) |
| **0.5s** | 2 | Lane change begins 0.5 seconds after the turn signal is activated |
| **1s** | 3 | Lane change begins 1 second after activation |
| **2s** | 4 | Lane change begins 2 seconds after activation |
| **3s** | 5 | Lane change begins 3 seconds after activation |

---

## BSM Delay

| Property | Value |
|----------|-------|
| **Param** | `AutoLaneChangeBsmDelay` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

When enabled, the system waits for the blind spot to clear before executing a lane change. If a vehicle is detected in the blind spot, the lane change is delayed until the path is clear.

!!! info "Requirements"
    - Vehicle must support Blind Spot Monitoring (BSM) — only shown when `enableBsm` is true in car parameters
    - Auto Lane Change Timer must be set to a mode beyond Nudge (i.e., Nudgeless or a timed option)

---

## Related Features

- [Auto Lane Change](../features/auto-lane-change.md)
