#!/usr/bin/env python3
"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import json
import os
import re
import sys
from collections import OrderedDict

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
BASEDIR = os.path.normpath(os.path.join(SCRIPT_DIR, "..", "..", ".."))
SETTINGS_UI_PATH = os.path.join(SCRIPT_DIR, "..", "settings_ui.json")
PARAMS_KEYS_PATH = os.path.join(BASEDIR, "common", "params_keys.h")
TORQUE_VERSIONS_PATH = os.path.join(BASEDIR, "sunnypilot", "selfdrive", "controls", "lib", "latcontrol_torque_versions.json")

# Hardcoded option generators (matching update_params_metadata.py logic)
ONROAD_BRIGHTNESS_OPTIONS = (
  [
    {"value": 0, "label": "Auto (Default)"},
    {"value": 1, "label": "Auto (Dark)"},
    {"value": 2, "label": "Screen Off"},
  ]
  + [{"value": i, "label": f"{(i - 2) * 5} %"} for i in range(3, 23)]
)

ONROAD_TIMER_VALUES = {
  0: 0,
  1: 3,
  2: 5,
  3: 10,
  4: 15,
  5: 30,
  6: 60,
  7: 180,
  8: 300,
  9: 600,
}


def parse_params_keys(path: str) -> list[str]:
  """Parse param key names from params_keys.h."""
  pattern = re.compile(r'^\s*\{"(\w+)"')
  keys = []
  with open(path) as f:
    for line in f:
      match = pattern.match(line)
      if match:
        keys.append(match.group(1))
  return sorted(set(keys))


def collect_ui_keys(data: dict) -> set[str]:
  """Walk settings_ui.json and collect all item keys."""
  keys: set[str] = set()

  def walk_items(items: list[dict]) -> None:
    for item in items:
      if "key" in item:
        keys.add(item["key"])
      for sub_item in item.get("sub_items", []):
        if "key" in sub_item:
          keys.add(sub_item["key"])

  def walk_sub_panels(sub_panels: list[dict]) -> None:
    for sp in sub_panels:
      walk_items(sp.get("items", []))

  for panel in data.get("panels", []):
    for section in panel.get("sections", []):
      walk_items(section.get("items", []))
      walk_sub_panels(section.get("sub_panels", []))

  for _brand, brand_data in data.get("vehicle_settings", {}).items():
    walk_items(brand_data.get("items", []))

  return keys


def find_item_by_key(data: dict, target_key: str) -> dict | None:
  """Find and return the item dict with matching key (mutable reference)."""

  def search_items(items: list[dict]) -> dict | None:
    for item in items:
      if item.get("key") == target_key:
        return item
      for sub_item in item.get("sub_items", []):
        if sub_item.get("key") == target_key:
          return sub_item
    return None

  for panel in data.get("panels", []):
    for section in panel.get("sections", []):
      result = search_items(section.get("items", []))
      if result is not None:
        return result
      for sp in section.get("sub_panels", []):
        result = search_items(sp.get("items", []))
        if result is not None:
          return result

  for _brand, brand_data in data.get("vehicle_settings", {}).items():
    result = search_items(brand_data.get("items", []))
    if result is not None:
      return result

  return None


def generate_torque_options(path: str) -> list[dict]:
  """Generate TorqueControlTune options from torque versions JSON."""
  with open(path) as f:
    versions = json.load(f)
  options = [{"value": "", "label": "Default"}]
  for version_key, version_data in versions.items():
    version_value = float(version_data["version"])
    options.append({"value": version_value, "label": str(version_key)})
  return options


def generate_onroad_timer_options() -> list[dict]:
  """Generate OnroadScreenOffTimer options."""
  options = []
  for _index, seconds in sorted(ONROAD_TIMER_VALUES.items()):
    if seconds == 0:
      label = "Always On"
    elif seconds < 60:
      label = f"{seconds}s"
    else:
      label = f"{seconds // 60}m"
    options.append({"value": seconds, "label": label})
  return options


def report_new_params(params_keys: list[str], ui_keys: set[str]) -> None:
  """Print params in params_keys.h that are NOT in settings_ui.json."""
  missing = sorted(k for k in params_keys if k not in ui_keys)
  if missing:
    print(f"\n[INFO] {len(missing)} param(s) in params_keys.h without settings_ui.json entry:")
    for key in missing:
      print(f"  - {key}")
  else:
    print("\n[INFO] All params_keys.h keys have settings_ui.json entries.")


def validate_items(data: dict) -> int:
  """Validate completeness of items in settings_ui.json. Returns warning count."""
  warnings = 0

  def check_item(item: dict, context: str) -> int:
    count = 0
    key = item.get("key", "<unknown>")
    widget = item.get("widget", "")

    if "title" not in item:
      print(f"  [WARN] {context} > {key}: missing 'title' field")
      count += 1

    if item.get("title") == key:
      print(f"  [WARN] {context} > {key}: title is same as key (default placeholder?)")
      count += 1

    if widget in ("multiple_button", "option") and "options" not in item:
      has_range = "min" in item or "max" in item
      if not has_range:
        print(f"  [WARN] {context} > {key}: widget '{widget}' has no 'options' and no min/max")
        count += 1

    return count

  def check_items(items: list[dict], context: str) -> int:
    count = 0
    for item in items:
      count += check_item(item, context)
      for sub_item in item.get("sub_items", []):
        count += check_item(sub_item, f"{context} > sub_items")
    return count

  for panel in data.get("panels", []):
    panel_ctx = f"panels/{panel.get('id', '?')}"
    for section in panel.get("sections", []):
      section_ctx = f"{panel_ctx}/{section.get('id', '?')}"
      warnings += check_items(section.get("items", []), section_ctx)
      for sp in section.get("sub_panels", []):
        sp_ctx = f"{section_ctx}/{sp.get('id', '?')}"
        warnings += check_items(sp.get("items", []), sp_ctx)

  for brand, brand_data in data.get("vehicle_settings", {}).items():
    warnings += check_items(brand_data.get("items", []), f"vehicle_settings/{brand}")

  return warnings


def main() -> int:
  # Load settings_ui.json preserving key order
  with open(SETTINGS_UI_PATH) as f:
    data = json.load(f, object_pairs_hook=OrderedDict)

  # 1. Report new params
  params_keys = parse_params_keys(PARAMS_KEYS_PATH)
  ui_keys = collect_ui_keys(data)
  report_new_params(params_keys, ui_keys)

  # 2. Auto-sync option lists
  changed = False

  # TorqueControlTune
  if os.path.exists(TORQUE_VERSIONS_PATH):
    new_options = generate_torque_options(TORQUE_VERSIONS_PATH)
    item = find_item_by_key(data, "TorqueControlTune")
    if item is not None:
      old_options = item.get("options")
      if old_options != new_options:
        item["options"] = new_options
        changed = True
        print(f"\n[SYNC] TorqueControlTune: updated options ({len(new_options)} entries)")
      else:
        print(f"\n[SYNC] TorqueControlTune: options already up to date")
    else:
      print("\n[WARN] TorqueControlTune item not found in settings_ui.json")
  else:
    print(f"\n[WARN] Torque versions file not found: {TORQUE_VERSIONS_PATH}")

  # OnroadScreenOffBrightness
  item = find_item_by_key(data, "OnroadScreenOffBrightness")
  if item is not None:
    old_options = item.get("options")
    if old_options != ONROAD_BRIGHTNESS_OPTIONS:
      item["options"] = ONROAD_BRIGHTNESS_OPTIONS
      changed = True
      print(f"[SYNC] OnroadScreenOffBrightness: updated options ({len(ONROAD_BRIGHTNESS_OPTIONS)} entries)")
    else:
      print("[SYNC] OnroadScreenOffBrightness: options already up to date")

  # OnroadScreenOffTimer
  timer_options = generate_onroad_timer_options()
  item = find_item_by_key(data, "OnroadScreenOffTimer")
  if item is not None:
    old_options = item.get("options")
    if old_options != timer_options:
      item["options"] = timer_options
      changed = True
      print(f"[SYNC] OnroadScreenOffTimer: updated options ({len(timer_options)} entries)")
    else:
      print("[SYNC] OnroadScreenOffTimer: options already up to date")

  # 3. Validate completeness
  print("\n[VALIDATE] Checking item completeness...")
  warning_count = validate_items(data)
  if warning_count == 0:
    print("  No warnings.")
  else:
    print(f"  {warning_count} warning(s) found.")

  # 4. Write back only if auto-sync changed something
  if changed:
    with open(SETTINGS_UI_PATH, "w") as f:
      json.dump(data, f, indent=2)
      f.write("\n")
    print(f"\n[WRITE] Updated {SETTINGS_UI_PATH}")
  else:
    print(f"\n[SKIP] No auto-sync changes; {SETTINGS_UI_PATH} unchanged.")

  return 0


if __name__ == "__main__":
  sys.exit(main())
