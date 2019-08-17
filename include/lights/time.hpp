#ifndef LIGHT_SCHEDULER_TIME_H
#define LIGHT_SCHEDULER_TIME_H

#include <functional>
#include <ostream>

namespace lights {

enum class Frequency {
  EveryDay,
};

enum class Day {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday,

  EveryDay,
  Weekend,
};

struct Time {
  int minute_of_day;
  Day day_of_week;

  Time() : minute_of_day(0), day_of_week(Day::Monday) {}
  Time(int minute, Day day) : minute_of_day(minute), day_of_week(day) {}

  bool operator==(const Time &other) const {
    return day_of_week == other.day_of_week &&
           minute_of_day == other.minute_of_day;
  }
};

Time get_time();

// A handle which can be used to cancel an alarm after it has been scheduled.
using AlarmID = int;
// An value representing an invalid alarm ID.
const AlarmID InvalidAlarmID = 0;

// Schedules a callback to be invoked @seconds in the future.
AlarmID set_periodic_alarm(int seconds, std::function<void()> callback);

// Cancels an alarm which was previously created with @set_periodic_alarm.
void cancel_periodic_alarm(AlarmID id);

inline std::ostream &operator<<(std::ostream &outs, const Day &day) {
  switch (day) {
  case Day::Monday:
    return outs << "Monday";
  case Day::Tuesday:
    return outs << "Tuesday";
  case Day::Wednesday:
    return outs << "Wednesday";
  case Day::Thursday:
    return outs << "Thursday";
  case Day::Friday:
    return outs << "Friday";
  case Day::Saturday:
    return outs << "Saturday";
  case Day::Sunday:
    return outs << "Sunday";
  case Day::EveryDay:
    return outs << "EveryDay";
  case Day::Weekend:
    return outs << "Weekend";
  default:
    return outs << "<unknown day>";
  }
}

} // namespace lights

#endif // LIGHT_SCHEDULER_TIME_H
