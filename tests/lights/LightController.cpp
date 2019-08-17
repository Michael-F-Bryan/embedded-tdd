#include "lights/LightController.hpp"
#include "fake_light_controller.hpp"
#include <optional>

std::optional<lights::LightID> last_id;
std::optional<lights::LightState> last_state;

namespace lights {

void turn_on(LightID id) {
  fake_light_controller::set_last_id(id);
  fake_light_controller::set_last_state(LightState::On);
}

void turn_off(LightID id) {
  fake_light_controller::set_last_id(id);
  fake_light_controller::set_last_state(LightState::Off);
}

} // namespace lights

namespace fake_light_controller {

std::optional<lights::LightID> last_id() { return ::last_id; }
void set_last_id(std::optional<lights::LightID> id) { ::last_id = id; }
std::optional<lights::LightState> last_state() { return ::last_state; }
void set_last_state(std::optional<lights::LightState> state) {
  ::last_state = state;
}

} // namespace fake_light_controller