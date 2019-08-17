#include "lights/LightController.hpp"
#include "lights/internal.hpp"

namespace lights {

void turn_on(LightID id) {
  set_last_id(id);
  set_last_state(LightState::On);
}

void turn_off(LightID id) {
  set_last_id(id);
  set_last_state(LightState::Off);
}

} // namespace lights