#ifndef FAKE_LIGHT_CONTROLLER_H
#define FAKE_LIGHT_CONTROLLER_H

#include "lights/LightController.hpp"
#include <optional>

namespace fake_light_controller {

std::optional<lights::LightID> last_id();
void set_last_id(std::optional<lights::LightID> id);
std::optional<lights::LightState> last_state();
void set_last_state(std::optional<lights::LightState> state);

} // namespace fake_light_controller

#endif // of FAKE_LIGHT_CONTROLLER_H