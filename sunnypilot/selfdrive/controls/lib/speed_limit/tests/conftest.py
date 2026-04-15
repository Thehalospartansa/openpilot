"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""

import pytest

from cereal import custom, car
from opendbc.car.car_helpers import interfaces
from opendbc.car.toyota.values import CAR as TOYOTA
from openpilot.common.constants import CV
from openpilot.common.params import Params
from openpilot.sunnypilot.selfdrive.car import interfaces as sunnypilot_interfaces
from openpilot.sunnypilot.selfdrive.controls.lib.speed_limit.speed_limit_assist import SpeedLimitAssist
from openpilot.sunnypilot.selfdrive.controls.lib.speed_limit.common import Mode
from openpilot.sunnypilot.selfdrive.selfdrived.events import EventsSP

SpeedLimitAssistState = custom.LongitudinalPlanSP.SpeedLimit.AssistState


class CarParamsFactory:
  @staticmethod
  def create_car_interface(car_name: str = TOYOTA.TOYOTA_RAV4_TSS2) -> tuple[car.CarParams, custom.CarParamsSP, object]:
    params = Params()
    CarInterface = interfaces[car_name]
    CP = CarInterface.get_non_essential_params(car_name)
    CP_SP = CarInterface.get_non_essential_params_sp(CP, car_name)
    CI = CarInterface(CP, CP_SP)
    CI.CP.openpilotLongitudinalControl = True
    sunnypilot_interfaces.setup_interfaces(CI, params)
    return CI.CP, CI.CP_SP, CI


class SpeedLimitAssistScenario:
  def __init__(self, CP: car.CarParams, CP_SP: custom.CarParamsSP, params: Params = None):
    if params is None:
      params = Params()
    self.params = params
    self.CP = CP
    self.CP_SP = CP_SP
    self.params.put("SpeedLimitMode", int(Mode.assist))
    self.sla = SpeedLimitAssist(CP, CP_SP)
    self.sla.update_params()
    self.events_sp = EventsSP()
    self.speed_conv = CV.MS_TO_KPH if self.sla.is_metric else CV.MS_TO_MPH

  def set_state(self, state: int) -> "SpeedLimitAssistScenario":
    self.sla.state = state
    return self

  def set_speed_limits(self, speed_limit: float, distance: float = 0, speed_limit_final_last: float = 0,
                       speed_limit_prev: float = 0) -> "SpeedLimitAssistScenario":
    self.sla._speed_limit = speed_limit
    self.sla._distance = distance
    self.sla.speed_limit_prev = speed_limit_prev
    return self

  def set_cruise_speeds(self, v_cruise_cluster: float, v_cruise_cluster_prev: float = None) -> "SpeedLimitAssistScenario":
    self.sla.v_cruise_cluster = v_cruise_cluster
    if v_cruise_cluster_prev is None:
      v_cruise_cluster_prev = v_cruise_cluster
    self.sla.v_cruise_cluster_prev = v_cruise_cluster_prev
    self.sla.prev_v_cruise_cluster_conv = round(v_cruise_cluster_prev * self.speed_conv)
    return self

  def set_engaged(self, op_engaged: bool) -> "SpeedLimitAssistScenario":
    self.sla.op_engaged = op_engaged
    return self

  def set_param(self, key: str, value) -> "SpeedLimitAssistScenario":
    # IntEnum instances carry a .value the Params API does not accept directly
    if hasattr(value, 'value'):
      value = value.value

    if isinstance(value, bool):
      self.params.put_bool(key, value)
    elif isinstance(value, int):
      self.params.put(key, value)
    else:
      self.params.put(key, str(value) if not isinstance(value, str) else value)
    return self

  def clear_events(self) -> "SpeedLimitAssistScenario":
    self.events_sp.clear()
    return self

  def reset_state(self) -> "SpeedLimitAssistScenario":
    self.sla.state = SpeedLimitAssistState.disabled
    self.sla.frame = -1
    self.sla.long_enabled = False
    self.sla.long_enabled_prev = False
    self.sla._speed_limit = 0.0
    self.sla.speed_limit_prev = 0.0
    self.sla._speed_limit_final_last = 0.0
    self.sla._distance = 0.0
    self.sla.long_engaged_timer = 0
    self.sla.pre_active_timer = 0
    self.events_sp.clear()
    return self

  def build(self) -> "SpeedLimitAssistScenario":
    return self


@pytest.fixture
def params():
  p = Params()
  yield p


@pytest.fixture
def car_params_factory():
  return CarParamsFactory()


@pytest.fixture
def scenario_builder(params):
  def builder(car_name: str = TOYOTA.TOYOTA_RAV4_TSS2) -> SpeedLimitAssistScenario:
    CP, CP_SP, _ = CarParamsFactory.create_car_interface(car_name)
    return SpeedLimitAssistScenario(CP, CP_SP, params)
  return builder
