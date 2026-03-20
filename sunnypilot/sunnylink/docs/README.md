# sunnylink Settings UI Definition Guide

> How to add, change, or update params/settings that appear on the sunnylink frontend — without modifying any frontend code.

## Overview

The sunnylink frontend renders its settings UI entirely from a **device-generated schema**. Two files in the sunnypilot repo control what the frontend displays:

| File | What you control | Examples |
|------|-----------------|---------|
| `sunnypilot/sunnylink/settings_ui.json` | Structure, layout, widget types, visibility/enablement rules | Where a toggle appears, when it's shown/hidden, when it's greyed out |
| `sunnypilot/sunnylink/params_metadata.json` | Display text and value constraints | Titles, descriptions, option labels, min/max/step/unit |

**The frontend renders whatever the device sends.** No frontend PR needed.

---

## Quick Start

### Adding a new toggle (minimum viable change)

**1. Register the param** in `common/params_keys.h`:
```cpp
{"MyNewToggle", {PERSISTENT | BACKUP, BOOL}},
```

**2. Add display metadata** in `sunnypilot/sunnylink/params_metadata.json`:
```json
"MyNewToggle": {
  "title": "My New Feature",
  "description": "Enable the new feature for enhanced driving."
}
```

**3. Place it in the UI** in `sunnypilot/sunnylink/settings_ui.json`:

Find the panel and section where it belongs, then add to the `items` array:
```json
{
  "key": "MyNewToggle",
  "widget": "toggle",
  "enablement": [{"type": "offroad_only"}]
}
```

**4. Validate:**
```bash
python sunnypilot/sunnylink/tools/validate_settings_ui.py
```

**5. Commit.** The frontend will render it on the next device boot.

---

## File Structure

```
sunnypilot/sunnylink/
  settings_ui.json            <-- UI structure (you edit this)
  settings_ui.schema.json     <-- JSON Schema for IDE autocomplete
  params_metadata.json        <-- Display text and options (you edit this)
  capabilities.py             <-- Car capability fields (reference)
  tools/
    validate_settings_ui.py   <-- Run this after every edit
    generate_settings_schema.py  <-- Merges definition + metadata at boot
    extract_settings_ui.py    <-- One-time extraction tool (historical)
```

---

## How It Works

```
settings_ui.json     +     params_metadata.json
  (structure/rules)           (titles/options/ranges)
        |                            |
        +---------- MERGE ----------+
                      |
                      v
              gzip + base64 encode
                      |
                      v
              SettingsSchema param (stored on device)
                      |
                      v (fetched via getParams RPC)
              sunnylink frontend
              (decodes, decompresses, renders)
```

At device boot, the generator:
1. Reads `settings_ui.json` for structure and rules
2. Reads `params_metadata.json` for titles, descriptions, options
3. Merges them together
4. Compresses (gzip) and base64-encodes
5. Writes to the `SettingsSchema` param

The frontend fetches this param, decompresses it, and renders the UI.

---

## settings_ui.json Structure

### Hierarchy

```
Root
  panels[]                    <-- Top-level navigation categories
    sections[]                <-- Grouped cards within a panel (V2)
      items[]                 <-- Individual settings
        sub_items[]           <-- Nested settings revealed by parent
      sub_panels[]            <-- Drill-down pages (chevron rows)
    items[]                   <-- Flat items (panels without sections)
  vehicle_settings{}          <-- Brand-specific settings (by brand key)
```

### Panel (top-level category)

```json
{
  "id": "steering",
  "label": "Steering",
  "icon": "steering_wheel",
  "order": 1,
  "description": "Lateral control, lane changes, and steering behavior",
  "remote_configurable": true,
  "sections": [...]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `id` | Yes | Unique identifier, matches the URL path (`/dashboard/settings/{id}`) |
| `label` | Yes | Display name in the sidebar navigation |
| `icon` | Yes | Icon identifier |
| `order` | Yes | Sort order in navigation (must be unique across panels) |
| `description` | No | Subtitle shown below the panel heading |
| `remote_configurable` | No | Whether the frontend can push changes (default: `true`) |
| `sections` | No | Array of grouped sections (use this OR `items`, not both) |
| `items` | No | Array of flat items (for simple panels without grouping) |

### Section (grouped card within a panel)

```json
{
  "id": "mads",
  "title": "MADS",
  "description": "Modified Assistive Driving Safety",
  "order": 1,
  "items": [...],
  "sub_panels": [...]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `id` | Yes | Unique within the panel |
| `title` | Yes | Section header displayed above the card |
| `description` | No | Subtitle below the section header |
| `order` | No | Sort order within the panel (falls back to array position) |
| `items` | No | Settings within this section |
| `sub_panels` | No | Drill-down pages triggered by items in this section |

### Item (individual setting)

```json
{
  "key": "Mads",
  "widget": "toggle",
  "visibility": [...],
  "enablement": [{"type": "offroad_only"}]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `key` | Yes | Param key name (must exist in `params_keys.h`) |
| `widget` | Yes | One of: `toggle`, `option`, `multiple_button`, `button`, `info` |
| `visibility` | No | Rules that control show/hide (all must pass) |
| `enablement` | No | Rules that control enabled/disabled (all must pass) |
| `sub_items` | No | Child items that appear indented below this item |
| `title` | No | Override title (normally comes from metadata) |
| `description` | No | Override description (normally comes from metadata) |

### Sub-Panel (drill-down page)

```json
{
  "id": "mads_settings",
  "label": "MADS Settings",
  "trigger_key": "Mads",
  "trigger_condition": {
    "type": "param",
    "key": "Mads",
    "equals": true
  },
  "items": [...]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `id` | Yes | Unique identifier |
| `label` | Yes | Text shown on the chevron row |
| `trigger_key` | Yes | Param key that this sub-panel relates to (must exist in same panel) |
| `trigger_condition` | No | Rule that controls when the sub-panel row is visible |
| `items` | No | Settings shown when the sub-panel is opened |

---

## Widget Types

| Widget | Renders as | Use when |
|--------|-----------|----------|
| `toggle` | On/off switch | Boolean param (`BOOL` type) |
| `multiple_button` | Segmented button group | Param with 2-4 discrete options |
| `option` | Dropdown or slider | Param with many options, or numeric range with `min`/`max` |
| `info` | Read-only text display | Display-only values (e.g., language) |
| `button` | Action button | Triggering an action (rarely used) |

**How the frontend decides dropdown vs slider for `option` widget:**
- If metadata has `min`/`max`/`step` -> renders as a **slider**
- If metadata has `options` array -> renders as a **dropdown**

**How the frontend handles `multiple_button` overflow:**
- Fits on screen -> **segmented buttons** (pill-shaped)
- Too many options -> **compact mode** (smaller text)
- Still overflows -> **dropdown fallback**

---

## params_metadata.json Patterns

Metadata provides display text and value constraints. The generator merges these into items automatically -- you do NOT need to duplicate them in `settings_ui.json`.

### Simple toggle (title only)

```json
"Mads": {
  "title": "MADS Enabled",
  "description": ""
}
```

### Toggle with description

```json
"GreenLightAlert": {
  "title": "Green Traffic Light Alert (Beta)",
  "description": "A chime will play when the traffic light turns green and you have no vehicle in front of you."
}
```

### Option selector (discrete values)

```json
"AutoLaneChangeTimer": {
  "title": "Auto Lane Change Timer",
  "description": "",
  "options": [
    {"value": -1, "label": "Off"},
    {"value": 0, "label": "Nudge"},
    {"value": 1, "label": "Nudgeless"},
    {"value": 2, "label": "0.5s"},
    {"value": 3, "label": "1s"},
    {"value": 4, "label": "1.5s"},
    {"value": 5, "label": "2s"}
  ]
}
```

### Numeric range (slider)

```json
"CameraOffset": {
  "title": "Adjust Camera Offset",
  "description": "Virtually shift camera's perspective.",
  "min": -0.35,
  "max": 0.35,
  "step": 0.01,
  "unit": "meters"
}
```

### Numeric range (integer)

```json
"CustomAccLongPressIncrement": {
  "title": "Custom ACC Long Press Increment",
  "description": "",
  "min": 1,
  "max": 10,
  "step": 1
}
```

### Description with line breaks

Use `<br>` tags for line breaks (only `<br>` is allowed, all other HTML is stripped):

```json
"SomeParam": {
  "title": "Feature Name",
  "description": "First line of explanation.<br>Second line with more detail."
}
```

---

## Rules Reference

Rules control **visibility** (show/hide) and **enablement** (enabled/greyed out).

- `visibility` rules: if ANY rule fails, the item is **completely hidden**
- `enablement` rules: if ANY rule fails, the item is **visible but greyed out**
- All rules in an array use **AND** logic (all must pass)
- Empty array or no rules = always visible/enabled

### offroad_only

Only passes when the device is not actively driving.

```json
{"type": "offroad_only"}
```

Use in `enablement` (not `visibility`) so users can see the setting exists but know they need to stop to change it. The frontend shows an "Offroad" badge.

### capability

Checks a vehicle capability derived from CarParams at runtime.

```json
{"type": "capability", "field": "has_longitudinal_control", "equals": true}
```

```json
{"type": "capability", "field": "brand", "equals": "toyota"}
```

```json
{"type": "capability", "field": "steer_control_type", "equals": "angle"}
```

**Available capability fields:**

| Field | Type | Description |
|-------|------|-------------|
| `has_longitudinal_control` | bool | Car supports openpilot longitudinal |
| `has_icbm` | bool | Intelligent Cruise Button Management active |
| `icbm_available` | bool | ICBM is available for this car |
| `torque_allowed` | bool | Torque lateral control supported |
| `brand` | string | Vehicle brand (e.g., "toyota", "hyundai") |
| `pcm_cruise` | bool | PCM cruise control |
| `alpha_long_available` | bool | Alpha longitudinal available |
| `steer_control_type` | string | Steering control type (e.g., "angle", "torque") |
| `enable_bsm` | bool | Blind spot monitoring available |
| `is_release` | bool | Running release branch |
| `is_sp_release` | bool | Running sunnypilot release branch |
| `is_development` | bool | Running development branch |
| `tesla_has_vehicle_bus` | bool | Tesla with vehicle bus access |
| `has_stop_and_go` | bool | Stop and go capability |
| `stock_longitudinal` | bool | Using stock longitudinal control |

### param

Checks the current value of another param.

```json
{"type": "param", "key": "Mads", "equals": true}
```

```json
{"type": "param", "key": "SpeedLimitMode", "equals": 0}
```

### param_compare

Numeric comparison against another param's value.

```json
{"type": "param_compare", "key": "AutoLaneChangeTimer", "op": ">", "value": 0}
```

| Operator | Meaning |
|----------|---------|
| `>` | Greater than |
| `<` | Less than |
| `>=` | Greater than or equal |
| `<=` | Less than or equal |

### not

Negates a single rule.

```json
{
  "type": "not",
  "condition": {
    "type": "capability",
    "field": "steer_control_type",
    "equals": "angle"
  }
}
```

### any (OR logic)

Passes if **at least one** child condition passes.

```json
{
  "type": "any",
  "conditions": [
    {"type": "capability", "field": "has_longitudinal_control", "equals": true},
    {"type": "capability", "field": "has_icbm", "equals": true}
  ]
}
```

### all (AND logic)

Passes if **all** child conditions pass. (Note: a plain array of rules already uses AND logic. Use `all` inside `any` or `not` for nested logic.)

```json
{
  "type": "all",
  "conditions": [
    {"type": "param_compare", "key": "SpeedLimitMode", "op": ">", "value": 0},
    {"type": "param_compare", "key": "SpeedLimitOffsetType", "op": ">", "value": 0}
  ]
}
```

---

## Common Scenarios

### 1. Add a new toggle to an existing section

Find the panel and section, add to `items`:

```json
// In settings_ui.json, under device panel -> general section -> items
{
  "key": "FirehoseMode",
  "widget": "toggle",
  "enablement": [{"type": "offroad_only"}]
}
```

Add metadata:
```json
// In params_metadata.json
"FirehoseMode": {
  "title": "Firehose Mode",
  "description": "Upload all driving data continuously."
}
```

### 2. Add a multi-button selector with options

```json
// In settings_ui.json
{
  "key": "RecordingQuality",
  "widget": "multiple_button"
}
```

Options come from metadata:
```json
// In params_metadata.json
"RecordingQuality": {
  "title": "Recording Quality",
  "options": [
    {"value": 0, "label": "Low (720p)"},
    {"value": 1, "label": "Medium (1080p)"},
    {"value": 2, "label": "High (4K)"}
  ]
}
```

### 3. Add a slider/range control

```json
// In settings_ui.json
{
  "key": "FollowDistance",
  "widget": "option"
}
```

Range comes from metadata:
```json
// In params_metadata.json
"FollowDistance": {
  "title": "Follow Distance",
  "description": "Time gap to lead vehicle.",
  "min": 0.5,
  "max": 3.0,
  "step": 0.1,
  "unit": "seconds"
}
```

### 4. Show a setting only when another setting is enabled

```json
{
  "key": "BlinkerMinLateralControlSpeed",
  "widget": "option",
  "visibility": [
    {"type": "param", "key": "BlinkerPauseLateralControl", "equals": true}
  ]
}
```

### 5. Show a setting only for specific cars

```json
{
  "key": "SmartCruiseControlVision",
  "widget": "toggle",
  "visibility": [
    {
      "type": "any",
      "conditions": [
        {"type": "capability", "field": "has_longitudinal_control", "equals": true},
        {"type": "capability", "field": "has_icbm", "equals": true}
      ]
    }
  ]
}
```

### 6. Mutual exclusion (two toggles that can't both be on)

Each toggle's `enablement` requires the other to be `false`:

```json
{
  "key": "EnforceTorqueControl",
  "widget": "toggle",
  "enablement": [
    {"type": "offroad_only"},
    {"type": "param", "key": "NeuralNetworkLateralControl", "equals": false}
  ]
},
{
  "key": "NeuralNetworkLateralControl",
  "widget": "toggle",
  "enablement": [
    {"type": "offroad_only"},
    {"type": "param", "key": "EnforceTorqueControl", "equals": false}
  ]
}
```

Both toggles are visible. When one is on, the other is greyed out.

### 7. Add a new section to a panel

Add a section object to the panel's `sections` array:

```json
{
  "id": "comfort",
  "title": "Comfort",
  "description": "Steering feel and responsiveness tuning",
  "order": 5,
  "items": [
    {"key": "SteeringResponsiveness", "widget": "option"}
  ]
}
```

The frontend renders this as a new card with a "Comfort" header.

### 8. Add a sub-panel (drill-down page)

```json
{
  "id": "comfort",
  "title": "Comfort",
  "items": [
    {"key": "SteeringResponsiveness", "widget": "option"}
  ],
  "sub_panels": [
    {
      "id": "advanced_steering",
      "label": "Advanced Steering",
      "trigger_key": "SteeringResponsiveness",
      "items": [
        {"key": "SteeringDeadzone", "widget": "option"},
        {"key": "SteeringRampRate", "widget": "option"}
      ]
    }
  ]
}
```

A "Advanced Steering >" chevron row appears. Tapping it opens a slide-in sub-panel.

### 9. Add vehicle-specific settings

Add to `vehicle_settings` in `settings_ui.json`:

```json
"rivian": [
  {
    "key": "RivianOnePedalMode",
    "widget": "toggle",
    "enablement": [{"type": "offroad_only"}]
  }
]
```

Only users with a Rivian (where `capabilities.brand === "rivian"`) see this on the Vehicle page.

### 10. Change display text only

Edit only `params_metadata.json` -- no `settings_ui.json` change needed:

```json
"Mads": {
  "title": "M.A.D.S.",
  "description": "Modified Assistive Driving Safety -- keep lateral active without cruise."
}
```

### 11. Move a setting from one panel to another

1. Remove the item from its current panel/section in `settings_ui.json`
2. Add it to the target panel/section
3. Run the validator (catches duplicate keys if you forget to remove)

### 12. Reorder sections within a panel

Add or change `order` fields on the sections:

```json
{"id": "mads", "title": "MADS", "order": 1, ...},
{"id": "lane_change", "title": "Lane Change", "order": 2, ...},
{"id": "blinker", "title": "Blinker Control", "order": 3, ...},
{"id": "torque", "title": "Torque Control", "order": 4, ...}
```

Or simply reorder the items in the JSON array -- array position is used when `order` is not set.

### 13. Grey out a setting while driving

Use `enablement` with `offroad_only`:

```json
{
  "key": "MyParam",
  "widget": "toggle",
  "enablement": [{"type": "offroad_only"}]
}
```

The toggle is visible but disabled while driving. The frontend shows an "Offroad" badge.

### 14. Conditionally show a sub-panel

The sub-panel row only appears when `trigger_condition` passes:

```json
{
  "id": "torque_settings",
  "label": "Torque Settings",
  "trigger_key": "EnforceTorqueControl",
  "trigger_condition": {
    "type": "param",
    "key": "EnforceTorqueControl",
    "equals": true
  },
  "items": [...]
}
```

"Torque Settings >" only shows when "Enforce Torque Control" is on.

### 15. Complex nested rule: visible only when multiple conditions are met

```json
{
  "key": "SpeedLimitValueOffset",
  "widget": "option",
  "visibility": [
    {
      "type": "all",
      "conditions": [
        {"type": "param_compare", "key": "SpeedLimitMode", "op": ">", "value": 0},
        {"type": "param_compare", "key": "SpeedLimitOffsetType", "op": ">", "value": 0}
      ]
    }
  ]
}
```

This item is hidden unless BOTH SpeedLimitMode > 0 AND SpeedLimitOffsetType > 0.

---

## Validation

**Always run after editing `settings_ui.json`:**

```bash
python sunnypilot/sunnylink/tools/validate_settings_ui.py
```

The validator performs 10 checks:

| Check | What it catches |
|-------|----------------|
| JSON parseable | Syntax errors, trailing commas, missing brackets |
| Structural | Missing required fields (id, key, widget, etc.) |
| Param existence | Keys not found in params_metadata.json (warns, doesn't fail) |
| No duplicate keys | Same param key in multiple panels |
| Rule well-formedness | Invalid rule types, missing fields, bad operators |
| Capability refs | Capability field names that don't exist |
| No self-reference | Item whose rule references its own key |
| Sub-panel triggers | trigger_key that doesn't exist in the same panel |
| Ordering | Duplicate panel order values |
| Vehicle brands | Non-lowercase brand keys |

**Example output (all passing):**
```
OK: JSON parseable
OK: structural
OK: param existence
OK: no duplicate keys
OK: rule well-formedness
OK: capability refs
OK: no self-reference
OK: sub-panel triggers
OK: ordering
OK: vehicle brands

============================================================
Summary: 10 checks passed, 0 checks failed
Result: PASS
```

---

## IDE Support

`settings_ui.json` references a JSON Schema file for editor autocomplete:

```json
{
  "$schema": "./settings_ui.schema.json",
  ...
}
```

In VS Code or JetBrains IDEs, this provides:
- Autocomplete for field names
- Enum validation for widget types and rule types
- Red squiggles for structural errors
- Hover documentation

---

## Checklist

Before committing changes to `settings_ui.json` or `params_metadata.json`:

- [ ] Param registered in `common/params_keys.h` with correct type
- [ ] Metadata added in `params_metadata.json` (title required, description recommended)
- [ ] Item placed in correct panel/section in `settings_ui.json`
- [ ] Widget type matches the param type (toggle for BOOL, option/multiple_button for INT/FLOAT)
- [ ] Visibility rules use correct capability field names
- [ ] Enablement includes `offroad_only` for settings that should not change while driving
- [ ] `python sunnypilot/sunnylink/tools/validate_settings_ui.py` passes
- [ ] No metadata fields duplicated in `settings_ui.json` (title, description, options come from metadata)

---

## FAQ

**Q: Do I need to modify any frontend code?**
No. The frontend renders whatever the schema contains. All UI changes are made through `settings_ui.json` and `params_metadata.json`.

**Q: When does the frontend pick up my changes?**
At device boot, the generator reads both files, merges them, compresses the result, and writes it to the `SettingsSchema` param. The frontend fetches this when it connects to the device.

**Q: What if my param key doesn't exist in params_metadata.json yet?**
The validator warns but doesn't fail. The item will render without a title (showing the raw key name). Add metadata for a proper display name.

**Q: Can I override the title from metadata for a specific context?**
Yes. Add `"title": "Custom Title"` directly on the item in `settings_ui.json`. Item-level fields take precedence over metadata.

**Q: What's the difference between `visibility` and `enablement`?**
- `visibility`: hidden entirely when rules fail (user doesn't know it exists)
- `enablement`: visible but greyed out when rules fail (user sees it but can't change it)

**Q: How do I test my changes locally?**
Run the generator directly to see the full merged output:
```bash
python sunnypilot/sunnylink/tools/generate_settings_schema.py
```

**Q: What happens if I add a key that doesn't exist in params_keys.h?**
The validator warns about it. The frontend will render the item but won't be able to read/write the value (it won't exist in the device's param store).
