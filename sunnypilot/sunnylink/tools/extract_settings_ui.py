#!/usr/bin/env python3
"""
One-time extraction script: converts the current hardcoded Python panel
definitions into settings_ui.json.

This script reads the existing generate_settings_schema.py panel builders,
strips metadata fields (title, description, options, min, max, step, unit)
that come from params_metadata.json, and outputs a clean structural JSON
containing only: panels, sections, items (key + widget + rules), sub_panels,
and vehicle_settings.

Usage:
  python extract_settings_ui.py > ../settings_ui.json
"""
from __future__ import annotations

import json
import sys
import os

# Add repo root to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', '..'))

from openpilot.sunnypilot.sunnylink.tools.generate_settings_schema import (
  _steering_panel, _cruise_panel, _display_panel, _visuals_panel,
  _toggles_panel, _device_panel, _software_panel, _sunnylink_panel,
  _developer_panel, _models_panel, _vehicle_settings,
  SCHEMA_VERSION,
)

# Fields that come from params_metadata.json and should NOT be in the definition
METADATA_FIELDS = {"title", "description", "options", "min", "max", "step", "unit"}


def strip_metadata(item: dict) -> dict:
  """Remove metadata fields from an item dict, keeping only structural fields."""
  result = {}
  for key, value in item.items():
    if key in METADATA_FIELDS:
      continue
    if key == "sub_items" and isinstance(value, list):
      result[key] = [strip_metadata(si) for si in value]
    elif key == "items" and isinstance(value, list):
      result[key] = [strip_metadata(i) for i in value]
    else:
      result[key] = value
  return result


def strip_panel_metadata(panel: dict) -> dict:
  """Strip metadata from all items in a panel, including sections and sub_panels.

  If the panel has sections, drop the backward-compat flat items/sub_panels —
  the generator will reconstruct those from sections at runtime.
  """
  has_sections = bool(panel.get("sections"))
  result = {}
  for key, value in panel.items():
    # Drop backward-compat flat items/sub_panels when sections exist
    if has_sections and key in ("items", "sub_panels"):
      continue
    if key == "items" and isinstance(value, list):
      result[key] = [strip_metadata(i) for i in value]
    elif key == "sections" and isinstance(value, list):
      sections = []
      for section in value:
        s = dict(section)
        if "items" in s:
          s["items"] = [strip_metadata(i) for i in s["items"]]
        if "sub_panels" in s:
          s["sub_panels"] = [strip_sub_panel(sp) for sp in s["sub_panels"]]
        sections.append(s)
      result[key] = sections
    elif key == "sub_panels" and isinstance(value, list):
      result[key] = [strip_sub_panel(sp) for sp in value]
    else:
      result[key] = value
  return result


def strip_sub_panel(sp: dict) -> dict:
  """Strip metadata from sub_panel items."""
  result = dict(sp)
  if "items" in result:
    result["items"] = [strip_metadata(i) for i in result["items"]]
  return result


def main():
  panels = [
    _steering_panel(),
    _cruise_panel(),
    _display_panel(),
    _visuals_panel(),
    _toggles_panel(),
    _device_panel(),
    _software_panel(),
    _sunnylink_panel(),
    _developer_panel(),
    _models_panel(),
  ]

  # Convert panels to dicts and strip metadata
  panel_dicts = []
  for panel in panels:
    raw = panel.to_dict()
    stripped = strip_panel_metadata(raw)
    panel_dicts.append(stripped)

  # Convert vehicle settings and strip metadata
  vehicle_raw = _vehicle_settings()
  vehicle_stripped = {}
  for brand, items in vehicle_raw.items():
    vehicle_stripped[brand] = [strip_metadata(i) for i in items]

  definition = {
    "$schema": "./settings_ui.schema.json",
    "schema_version": SCHEMA_VERSION,
    "panels": panel_dicts,
    "vehicle_settings": vehicle_stripped,
  }

  print(json.dumps(definition, indent=2))


if __name__ == "__main__":
  main()
