#include "lights/internal.hpp"
#include "lights/LightScheduler.hpp"
#include <optional>

namespace lights {

static std::optional<LightID> _last_id;
static LightState _last_state = LightState::Unknown;

std::optional<LightID> last_id() { return _last_id; }

void set_last_id(std::optional<LightID> id) { _last_id = id; }

LightState last_state() { return _last_state; }

void set_last_state(LightState state) { _last_state = state; }

std::ostream &operator<<(std::ostream &outs, const LightState &state) {
  switch (state) {
  case LightState::Unknown:
    return outs << "Unknown";
  case LightState::Off:
    return outs << "Off";
  case LightState::On:
    return outs << "On";
  default:
    return outs << "<unknown state>";
  }
}

} // namespace lights