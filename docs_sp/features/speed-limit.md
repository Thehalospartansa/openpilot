---
title: Speed Limit Control
---

# Speed Limit Control

## What It Does

Speed Limit Control detects the current speed limit using map data and can automatically adjust your cruise speed to match. It offers four operating modes ranging from passive information display to active speed management.

## How It Works

1. sunnypilot reads speed limit data from downloaded OSM maps
2. Based on your chosen mode, it displays, warns, or actively adjusts your set speed
3. An optional offset (fixed or percentage) lets you cruise slightly above or below the limit

## Requirements

!!! info "Requirements"
    - Longitudinal control must be available, **or** [ICBM](icbm.md) must be enabled
    - For map-based limits: [OSM Maps](osm-maps.md) must be configured and downloaded

## How to Enable

**Settings** → **sunnypilot** → **Cruise Control** → **Speed Limit Control**

## Operating Modes

| Mode | Behavior |
|------|----------|
| **Off** | Speed limit data is not used |
| **Info** | Shows the current speed limit on the driving display |
| **Warning** | Shows the speed limit and alerts you when you're exceeding it |
| **Assist** | Automatically adjusts cruise speed to match the speed limit |

## Speed Offset

You can set an offset so your cruise speed differs from the exact limit:

- **Fixed offset:** Add or subtract a set number of km/h or mph (range: -30 to +30)
- **Percentage offset:** Apply a percentage above or below the limit

## Vehicle Restrictions

!!! warning "Vehicle Restrictions"
    - **Tesla:** Assist mode is disabled on release branches (Info and Warning still work)
    - **Rivian:** Assist mode is always disabled

## Settings Reference

See [Speed Limit Settings](../settings/speed-limit.md) for all configuration options.
