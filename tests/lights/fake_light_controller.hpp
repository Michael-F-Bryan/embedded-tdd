#ifndef FAKE_LIGHT_CONTROLLER_H
#define FAKE_LIGHT_CONTROLLER_H

#include "lights/LightController.hpp"
#include <optional>

namespace fake_light_controller {

void reset();
std::optional<lights::LightID> last_id();
void set_last_id(lights::LightID id);
std::optional<lights::LightState> last_state(lights::LightID id);
void set_last_state(lights::LightID id, std::optional<lights::LightState> state);

inline std::optional<lights::LightState> last_state() {
    auto id = last_id();

    return id.has_value() ? last_state(id.value()) : std::optional<lights::LightState>();
}

} // namespace fake_light_controller

#endif // of FAKE_LIGHT_CONTROLLER_H