#if !defined(LIGHT_SCHEDULER_INTERNAL_H)
#define LIGHT_SCHEDULER_INTERNAL_H

#include "LightScheduler.hpp"
#include <optional>

namespace light_scheduler {

enum class LightState {
  Unknown,
  On,
  Off,
};

std::optional<LightID> last_id();
void set_last_id(std::optional<LightID> id);

LightState last_state();
void set_last_state(LightState state);

} // namespace light_scheduler

#endif // LIGHT_SCHEDULER_INTERNAL_H