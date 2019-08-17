#include "lights/LightScheduler.hpp"
#include <exception>
#include <functional>
#include <limits>
#include <optional>

namespace lights {

struct ScheduledLightEvent {
  LightID light_id = 0;
  int minute_of_day = 0;
  Day day = Day::EveryDay;
  LightState state = LightState::On;

  constexpr ScheduledLightEvent(LightID id, int minute, LightState state,
                                Day day)
      : light_id(id), minute_of_day(minute), state(state), day(day) {}
  constexpr ScheduledLightEvent() {}
};

static std::optional<ScheduledLightEvent> scheduledEvent;

LightScheduler::LightScheduler() {
  scheduledEvent = std::optional<ScheduledLightEvent>();
}

void LightScheduler::turn_on(LightID light_id, Day day, int minute_of_day) {
  scheduledEvent =
      ScheduledLightEvent(light_id, minute_of_day, LightState::On, day);
}

void LightScheduler::turn_off(LightID light_id, Day day, int minute_of_day) {
  scheduledEvent =
      ScheduledLightEvent(light_id, minute_of_day, LightState::Off, day);
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

bool days_match(const Day &actual, const Day &mask) {
  switch (mask) {
  case Day::EveryDay:
    return true;
  case Day::Weekend:
    return actual == Day::Saturday || actual == Day::Sunday;
  default:
    return actual == mask;
  }
}

bool should_respond_now(const Time &now, const ScheduledLightEvent &event) {
  return event.minute_of_day == now.minute_of_day &&
         days_match(now.day_of_week, event.day);
}

void process_events_due_now(const Time &now, const ScheduledLightEvent &event) {
  if (should_respond_now(now, event)) {
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

AlarmID register_wakeup(int seconds,
                        std::shared_ptr<LightScheduler> &scheduler) {
  std::shared_ptr<LightScheduler> ptr = scheduler;
  auto callback = [=]() { scheduler->wake_up(); };

  return set_periodic_alarm(seconds, std::function<void()>(callback));
}

} // namespace lights
