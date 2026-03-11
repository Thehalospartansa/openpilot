---
title: Software Settings
---

# Software Settings

Manage software updates and branch selection.

**Location:** Settings → sunnypilot → Software

---

## Disable Updates

| Property | Value |
|----------|-------|
| **Param** | `DisableUpdates` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Prevents sunnypilot from checking for and applying software updates. When enabled, the device will remain on the current version indefinitely.

!!! warning "Reboot Required"
    Changing this setting requires a device reboot to take effect.

!!! info "Requirements"
    - Device must be offroad
    - Advanced Controls must be enabled (`ShowAdvancedControls`)

---

## Branch Switching

The Software panel also allows switching between different sunnypilot branches.

| Property | Value |
|----------|-------|
| **Param (target)** | `UpdaterTargetBranch` |
| **Param (available)** | `UpdaterAvailableBranches` |
| **Type** | Branch selector |

Select from available branches to switch your device to a different version of sunnypilot. See [Branch Definitions](../references/branch-definitions.md) and [Recommended Branches](../references/recommended-branches.md) for guidance on which branch to use.

!!! tip
    For daily driving, stick with the latest **release** branch. Only switch to staging or dev branches if you want to test new features.
