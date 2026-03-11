---
title: Intelligent Cruise Button Management
---

# Intelligent Cruise Button Management (ICBM)

## What It Does

ICBM allows sunnypilot to intercept and dynamically manage your vehicle's cruise control button presses. Instead of directly changing the set speed, button presses are routed through sunnypilot's logic, enabling features like Speed Limit Control and Smart Cruise Control on vehicles that don't natively support sunnypilot longitudinal control.

This is particularly useful for vehicles where sunnypilot cannot directly control the gas and brakes — ICBM gives you many of the same benefits by intelligently managing the cruise buttons.

## How It Works

1. You press the cruise speed button on your steering wheel
2. ICBM intercepts the button press
3. sunnypilot applies its logic (speed limits, map curves, etc.) to determine the appropriate speed change
4. The adjusted command is sent to the vehicle's cruise system

This happens transparently — from your perspective, the buttons work normally but with smarter behavior.

## Requirements

!!! info "Requirements"
    - Your vehicle must support ICBM — not all vehicles are compatible
    - If the ICBM toggle does not appear in settings, your vehicle is not supported

## How to Enable

**Settings** → **sunnypilot** → **Cruise Control** → **Intelligent Cruise Button Management**

## Features Unlocked by ICBM

When ICBM is enabled, the following features become available even on vehicles without native longitudinal control:

- **[Smart Cruise Control — Vision](scc-v.md)** — Vision-based adaptive speed adjustments
- **[Smart Cruise Control — Map](scc-m.md)** — Map-aware speed adjustments
- **[Custom ACC Increments](custom-acc-increments.md)** — Custom button press speed steps
- **[Speed Limit Control](speed-limit.md)** — Automatic speed limit matching

## Settings Reference

See [Cruise Control Settings](../settings/cruise.md) for all available options.
