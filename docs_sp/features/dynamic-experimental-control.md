---
title: Dynamic Experimental Control
---

# Dynamic Experimental Control (DEC)

## What It Does

DEC automatically switches between openpilot's standard and experimental driving modes based on real-time road conditions. Instead of manually toggling between modes, the system chooses the most appropriate mode for the current situation.

## How It Works

DEC monitors multiple driving signals and conditions:

- **Current speed** — Lower speeds suggest city driving
- **Turn detection** — Upcoming turns may need experimental mode
- **Stop signs and traffic lights** — Intersections benefit from experimental mode
- **Road type** — Highway vs. urban driving

Based on these signals, DEC switches between:

| Mode | Best For |
|------|----------|
| **Standard Mode** | Highway driving with steady speeds and clear lanes |
| **Experimental Mode** | City driving with stops, turns, and complex intersections |

## Requirements

!!! info "Requirements"
    - Longitudinal control must be available
    - Device must be offroad to enable/disable

## How to Enable

**Settings** → **sunnypilot** → **Cruise Control** → **Dynamic Experimental Control**

## Settings Reference

See [Cruise Control Settings](../settings/cruise.md) for configuration details.
