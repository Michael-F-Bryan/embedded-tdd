#include "lights/LightController.hpp"
#include "fake_light_controller.hpp"
#include <optional>
#include <unordered_map>

using namespace lights;

std::optional<LightID> last_id;
std::unordered_map<LightID, LightState> states;

namespace lights {

void turn_on(LightID id) {
  fake_light_controller::set_last_id(id);
  fake_light_controller::set_last_state(id, LightState::On);
}

void turn_off(LightID id) {
  fake_light_controller::set_last_id(id);
  fake_light_controller::set_last_state(id, LightState::Off);
}

} // namespace lights

namespace fake_light_controller {

void reset() {
  states.clear();
  ::last_id.reset();
}

std::optional<LightID> last_id() { return ::last_id; }
void set_last_id(LightID id) { ::last_id = id; }

std::optional<LightState> last_state(LightID id) {
  if (states.find(id) == states.end()) {
    return std::optional<LightState>();
  } else {
    return states.at(id);
  }
}

void set_last_state(LightID id, std::optional<LightState> state) {
  if (state.has_value()) {
    states[id] = state.value();
  } else {
    states.erase(id);
  }
}

} // namespace fake_light_controller