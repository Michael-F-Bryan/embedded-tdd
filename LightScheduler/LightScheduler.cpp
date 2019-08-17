#include "LightScheduler.hpp"
#include <optional>

using namespace light_scheduler;

void LightScheduler::turn_on(LightID light_id, Frequency frequency,
                             uint16_t time) {}

std::optional<LightScheduler::LightID> LightScheduler::last_id() const {
  return std::optional<LightScheduler::LightID>();
}

LightState LightScheduler::last_state() const { return LightState::Unknown; }

  void LightScheduler::wake_up() {}