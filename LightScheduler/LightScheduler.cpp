#include "LightScheduler.hpp"
#include "LightScheduler_internal.hpp"
#include <optional>

using namespace light_scheduler;

LightScheduler::LightScheduler() {
  set_last_id(std::optional<LightID>());
  set_last_state(LightState::Unknown);
}

void LightScheduler::turn_on(LightID light_id, Frequency frequency,
                             uint16_t time) {}

void LightScheduler::wake_up() {}