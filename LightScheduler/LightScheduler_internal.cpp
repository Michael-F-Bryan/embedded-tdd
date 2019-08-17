#include "LightScheduler_internal.hpp"
#include "LightScheduler.hpp"
#include <optional>

using namespace light_scheduler;

static std::optional<LightScheduler::LightID> last_id;
static LightState last_state = LightState::Unknown;

std::optional<LightScheduler::LightID> light_scheduler::last_id() {
  return ::last_id;
}

void light_scheduler::set_last_id(std::optional<LightScheduler::LightID> id) {
  ::last_id = id;
}

LightState light_scheduler::last_state() { return ::last_state; }

void light_scheduler::set_last_state(LightState state) { ::last_state = state; }