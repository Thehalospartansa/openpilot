# sunnylink Settings UI Guide

> Edit one JSON file, run the validator, commit. The sunnylink frontend updates automatically.

For detailed architecture, capability fields, parity analysis, and dialog mappings, see [REFERENCE.md](REFERENCE.md).

## The File You Edit

| File | What | When to edit |
|------|------|-------------|
| `settings_ui.json` | Structure, widget types, display text, options, rules - everything | Adding/moving/removing/renaming a setting |

All metadata (titles, descriptions, options, min/max/step/unit) lives **inline on each item**. There is no separate metadata file.

## Quick Reference: Widget Types

| Widget | Use for | Fields needed |
|--------|---------|---------------|
| `toggle` | On/off boolean | `title` |
| `multiple_button` | 2-4 discrete options | `title` + `options` array |
| `option` | Numeric range or dropdown | `title` + `min/max/step` or `options` |
| `info` | Read-only display | `title` |

## Quick Reference: Item Fields

| Field | Required | Description |
|-------|----------|-------------|
| `key` | Yes | Param key name (must exist in `params_keys.h`) |
| `widget` | Yes | `toggle`, `option`, `multiple_button`, `button`, `info` |
| `title` | Yes | Display name shown to the user |
| `description` | No | Explanatory text below the title |
| `options` | For selectors | Array of `{"value": 0, "label": "Off"}` objects |
| `min`, `max`, `step` | For sliders | Numeric range constraints |
| `unit` | No | Unit label (e.g., `"seconds"`, `"mph"`) |
| `visibility` | No | Rules for show/hide (all must pass) |
| `enablement` | No | Rules for enabled/disabled (all must pass) |
| `sub_items` | No | Nested child items |
| `needs_onroad_cycle` | No | `true` if changing this param triggers a system restart. Frontend shows a "Restart" badge. See [REFERENCE.md - Remote Onroad Cycle](REFERENCE.md#remote-onroad-cycle) |

## Quick Reference: Rule Types

| Rule | Example | Use for |
|------|---------|---------|
| `offroad_only` | `{"type": "offroad_only"}` | Grey out while driving |
| `capability` | `{"type": "capability", "field": "has_longitudinal_control", "equals": true}` | Car-dependent visibility |
| `param` | `{"type": "param", "key": "Mads", "equals": true}` | Show/enable based on another setting |
| `param_compare` | `{"type": "param_compare", "key": "SpeedLimitMode", "op": ">", "value": 0}` | Numeric comparison |
| `not` | `{"type": "not", "condition": {...}}` | Negate a rule |
| `any` | `{"type": "any", "conditions": [...]}` | OR logic |
| `all` | `{"type": "all", "conditions": [...]}` | AND logic (for nesting inside `any`/`not`) |

`visibility` = hidden when rules fail. `enablement` = greyed out when rules fail.

Capability fields: `has_longitudinal_control`, `has_icbm`, `icbm_available`, `torque_allowed`, `brand`, `pcm_cruise`, `alpha_long_available`, `steer_control_type`, `enable_bsm`, `is_release`, `is_sp_release`, `is_development`, `tesla_has_vehicle_bus`, `has_stop_and_go`, `stock_longitudinal`

---

## How To

### Add a new toggle

1. Register in `common/params_keys.h`:
   ```cpp
   {"MyToggle", {PERSISTENT | BACKUP, BOOL}},
   ```

2. Add to `settings_ui.json` in the right panel/section `items` array:
   ```json
   {
     "key": "MyToggle",
     "widget": "toggle",
     "title": "My Feature",
     "description": "What this feature does.",
     "enablement": [{"type": "offroad_only"}]
   }
   ```

   If the toggle requires an onroad cycle (system restart) to take effect:
   ```json
   {
     "key": "MyToggle",
     "widget": "toggle",
     "title": "My Feature",
     "description": "What this feature does.",
     "needs_onroad_cycle": true,
     "enablement": [{"type": "offroad_only"}]
   }
   ```

3. Validate: `python sunnypilot/sunnylink/tools/validate_settings_ui.py`

### Add a multi-button selector

```json
{
  "key": "MySelector",
  "widget": "multiple_button",
  "title": "Mode",
  "options": [
    {"value": 0, "label": "Off"},
    {"value": 1, "label": "On"},
    {"value": 2, "label": "Auto"}
  ]
}
```

### Add a slider/range

```json
{
  "key": "MyRange",
  "widget": "option",
  "title": "Follow Distance",
  "description": "Time gap to lead vehicle.",
  "min": 0.5,
  "max": 3.0,
  "step": 0.1,
  "unit": "seconds"
}
```

### Add a dropdown

```json
{
  "key": "MyDropdown",
  "widget": "option",
  "title": "Recording Quality",
  "options": [
    {"value": 0, "label": "Low (720p)"},
    {"value": 1, "label": "Medium (1080p)"},
    {"value": 2, "label": "High (4K)"}
  ]
}
```

### Show only when another setting is on

```json
{
  "key": "ChildSetting",
  "widget": "toggle",
  "title": "Child Feature",
  "visibility": [{"type": "param", "key": "ParentToggle", "equals": true}]
}
```

### Show only for certain cars

```json
{
  "key": "LongFeature",
  "widget": "toggle",
  "title": "Longitudinal Feature",
  "visibility": [{"type": "capability", "field": "has_longitudinal_control", "equals": true}]
}
```

### Mutual exclusion (only one can be on)

```json
{
  "key": "OptionA",
  "widget": "toggle",
  "title": "Option A",
  "enablement": [{"type": "param", "key": "OptionB", "equals": false}]
},
{
  "key": "OptionB",
  "widget": "toggle",
  "title": "Option B",
  "enablement": [{"type": "param", "key": "OptionA", "equals": false}]
}
```

### Add a new section

```json
{
  "id": "my_section",
  "title": "My Section",
  "description": "Optional subtitle",
  "items": [...]
}
```

### Add a sub-panel (drill-down page)

```json
{
  "id": "my_sub",
  "label": "Advanced Settings",
  "trigger_key": "ParentParam",
  "trigger_condition": {"type": "param", "key": "ParentParam", "equals": true},
  "items": [...]
}
```

### Add vehicle-specific settings

Add to `vehicle_settings` in `settings_ui.json`:
```json
"rivian": {
  "title": "Rivian Settings",
  "items": [
    {
      "key": "RivianFeature",
      "widget": "toggle",
      "title": "Rivian One Pedal",
      "enablement": [{"type": "offroad_only"}]
    }
  ]
}
```

### Change display text

Edit the `title` or `description` on the item in `settings_ui.json`.

### Move a setting between panels

Remove from source panel, add to target panel. Validator catches duplicates.

### Reorder sections

Set `order` field on sections, or reorder the JSON array.

---

## Pre-Commit Checklist

- [ ] Param registered in `common/params_keys.h`
- [ ] Item in `settings_ui.json` with correct widget type and `title`
- [ ] `offroad_only` enablement for settings that shouldn't change while driving
- [ ] `needs_onroad_cycle: true` for settings that trigger `OnroadCycleRequested` on the device UI
- [ ] `python sunnypilot/sunnylink/tools/validate_settings_ui.py` passes
