#include "fake_time.hpp"
#include "lights/LightScheduler.hpp"
#include <optional>
#include <unordered_map>

using namespace lights;

static Time now = Time();
static std::optional<int> alarm_period;
static std::optional<std::function<void()>> next_callback;

namespace lights {

Time get_time() { return now; }

AlarmID set_periodic_alarm(int seconds, std::function<void()> callback) {
  next_callback = callback;
  alarm_period = seconds;
}

void cancel_periodic_alarm(AlarmID id) {
  next_callback.reset();
  alarm_period.reset();
}

} // namespace lights

namespace fake_time {

void set_day(Day day) { now.day_of_week = day; }

void set_minute(uint16_t minute) { now.minute_of_day = minute; }

std::optional<int> get_alarm_period() { return alarm_period; }

std::optional<std::function<void()>> &next_callback() {
  return ::next_callback;
}

} // namespace fake_time
