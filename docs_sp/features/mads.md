---
title: Modular Assistive Driving System
---

# Modular Assistive Driving System (MADS)

## What It Does

MADS decouples lateral (steering) and longitudinal (speed) controls. In standard openpilot, engaging cruise control activates both steering and speed control together, and disengaging turns both off. With MADS, steering assistance can remain active independently — even when cruise control is off.

This means you can have lane-keeping assistance while controlling the gas and brakes yourself.

## How It Works

With MADS enabled:

- **Steering stays active** even when you cancel cruise control
- You can engage steering assistance independently of cruise
- You choose what happens to steering when cruise disengages (remain active, pause, or fully disengage)
- You can configure whether the main cruise button also activates steering

## Requirements

!!! info "Requirements"
    - Supported on most vehicles with sunnypilot lateral control

## How to Enable

**Settings** → **sunnypilot** → **Steering** → enable **M.A.D.S.**

Then configure the sub-settings in **MADS Settings**.

## Key Settings

| Setting | What It Controls |
|---------|-----------------|
| **Main Cruise Allowed** | Whether the cruise on/off button can activate MADS |
| **Unified Engagement Mode** | Whether engaging cruise also engages MADS automatically |
| **Steering Mode on Disengage** | What happens to steering when cruise disengages |

## Vehicle-Specific Behavior

Some vehicles operate in **limited MADS mode** where certain settings are locked:

=== "Tesla (without vehicle bus)"
    - Main Cruise Allowed: forced OFF
    - Unified Engagement Mode: forced ON
    - Steering Mode: forced to Disengage

=== "Rivian"
    - Main Cruise Allowed: forced OFF
    - Unified Engagement Mode: forced ON
    - Steering Mode: forced to Disengage

## Settings Reference

See [MADS Settings](../settings/mads.md) for all configuration options.

!!! warning "Safety"
    Always be ready to take full manual control. MADS allows more flexible use of driver assistance, but you remain responsible for safe driving at all times.
