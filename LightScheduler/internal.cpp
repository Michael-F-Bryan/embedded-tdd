#include "LightScheduler/internal.hpp"
#include "LightScheduler.hpp"
#include <optional>

namespace light_scheduler {

static std::optional<LightID> _last_id;
static LightState _last_state = LightState::Unknown;

std::optional<LightID> last_id() { return _last_id; }

void set_last_id(std::optional<LightID> id) { _last_id = id; }

LightState last_state() { return _last_state; }

void set_last_state(LightState state) { _last_state = state; }

}