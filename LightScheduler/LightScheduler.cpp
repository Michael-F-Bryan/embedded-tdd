#include "LightScheduler.hpp"
#include "LightScheduler/internal.hpp"
#include <limits>
#include <optional>

namespace light_scheduler {

struct ScheduledLightEvent {
  LightID light_id;
  int minute_of_day;
  LightState state;

  constexpr ScheduledLightEvent(LightID id, int minute, LightState state)
      : light_id(id), minute_of_day(minute), state(state) {}
  constexpr ScheduledLightEvent()
      : light_id(0), minute_of_day(0), state(LightState::Unknown) {}
};

static std::optional<ScheduledLightEvent> scheduledEvent;

LightScheduler::LightScheduler() {
  set_last_id(std::optional<LightID>());
  set_last_state(LightState::Unknown);
  scheduledEvent = std::optional<ScheduledLightEvent>();
}

void LightScheduler::turn_on(LightID light_id, Day day, int minute_of_day) {
  scheduledEvent = ScheduledLightEvent(light_id, minute_of_day, LightState::On);
}

void LightScheduler::turn_off(LightID light_id, Day day, int minute_of_day) {
  scheduledEvent =
      ScheduledLightEvent(light_id, minute_of_day, LightState::Off);
}

void LightScheduler::wake_up() {
  Time now = get_time();

  if (!scheduledEvent.has_value()) {
    return;
  }

  ScheduledLightEvent &event = scheduledEvent.value();

  if (now.minute_of_day != event.minute_of_day) {
    return;
  }

  switch (event.state) {
  case LightState::On:
    light_scheduler::turn_on(event.light_id);
    break;
  case LightState::Off:
    light_scheduler::turn_off(event.light_id);
    break;
  }
}

} // namespace light_scheduler