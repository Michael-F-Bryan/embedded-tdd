#ifndef FAKE_TIME_H
#define FAKE_TIME_H

#include "lights/LightScheduler.hpp"
#include <exception>
#include <optional>

namespace fake_time {

void set_day(lights::Day day);
void set_minute(uint16_t minute);

std::optional<int> get_alarm_period();

std::optional<std::function<void()>> &next_callback();

inline void set_time(lights::Day day, uint16_t minute) {
  if (day == lights::Day::EveryDay) {
    throw std::invalid_argument(
        "It doesn't make sense for today to be \"EveryDay\"");
  }

  set_day(day);
  set_minute(minute);
}

} // namespace fake_time

#endif // FAKE_TIME_H
