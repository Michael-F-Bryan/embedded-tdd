#include "LightScheduler.hpp"
#include "LightScheduler/internal.hpp"
#include <limits>
#include <optional>

namespace light_scheduler {

struct ScheduledLightEvent {
  LightID light_id;
  int minute_of_day;

  ScheduledLightEvent(LightID id, int minute)
      : light_id(id), minute_of_day(minute) {}
  ScheduledLightEvent() { ScheduledLightEvent(0, 0); }
};

static std::optional<ScheduledLightEvent> scheduledEvent;

LightScheduler::LightScheduler() {
  set_last_id(std::optional<LightID>());
  set_last_state(LightState::Unknown);
  scheduledEvent = std::optional<ScheduledLightEvent>();
}

void LightScheduler::turn_on(LightID light_id, Day day, int minute_of_day) {
  scheduledEvent = ScheduledLightEvent(light_id, minute_of_day);
}

void LightScheduler::wake_up() {
  Time now = get_time();

  if (!scheduledEvent.has_value()) {
    return;
  }

  ScheduledLightEvent& event = scheduledEvent.value();

  if (now.minute_of_day != event.minute_of_day) {
    return;
  }

  light_scheduler::turn_on(event.light_id);
}

}