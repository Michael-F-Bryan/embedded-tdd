#include "lights/LightScheduler.hpp"
#include "lights/internal.hpp"
#include <limits>
#include <optional>
#include <exception>

namespace lights {

struct ScheduledLightEvent {
  LightID light_id = 0;
  int minute_of_day = 0;
  LightState state = LightState::Unknown;

  constexpr ScheduledLightEvent(LightID id, int minute, LightState state)
      : light_id(id), minute_of_day(minute), state(state) {}
  constexpr ScheduledLightEvent() {}
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

void operate_light(const ScheduledLightEvent &event) {
  switch (event.state) {
  case LightState::On:
    lights::turn_on(event.light_id);
    break;
  case LightState::Off:
    lights::turn_off(event.light_id);
    break;
  default:
    throw std::invalid_argument("Invalid light state");
  }
}

void process_events_due_now(const Time &now, const ScheduledLightEvent &event) {
  if (now.minute_of_day == event.minute_of_day) {
    operate_light(event);
  }
}

void LightScheduler::wake_up() {
  if (!scheduledEvent.has_value()) {
    return;
  }

  Time now = get_time();
  process_events_due_now(now, scheduledEvent.value());
}

} // namespace lights
