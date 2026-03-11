---
title: SSH Method
---

# SSH Method

The SSH method provides more control over the installation process. Recommended for advanced users.

## Prerequisites

- SSH access to your comma device
- Basic familiarity with the command line

## Steps

1. Connect to your device via SSH
2. Clone the sunnypilot repository:
    ```bash
    cd /data
    git clone https://github.com/sunnypilot/sunnypilot.git openpilot
    ```
3. Check out the desired branch:
    ```bash
    cd openpilot
    git checkout <branch-name>
    ```
4. Reboot the device

See [Branch Definitions](../references/branch-definitions.md) for available branches.

## Troubleshooting

- **SSH connection refused**: Ensure SSH is enabled in device settings
- **Git clone fails**: Check internet connectivity
- **Branch not found**: Verify the branch name in [Recommended Branches](../references/recommended-branches.md)
