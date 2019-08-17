#include "LightController.hpp"
#include "LightScheduler/internal.hpp"

namespace light_scheduler {

void turn_on(LightID id) {
    set_last_id(id);
    set_last_state(LightState::On);
}

void turn_off(LightID id) {
    set_last_id(id);
    set_last_state(LightState::Off);
}

}