#if !defined(LIGHT_SCHEDULER_TIME_H)
#define LIGHT_SCHEDULER_TIME_H

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
void set_periodic_alarm();

} // namespace lights

#endif // LIGHT_SCHEDULER_TIME_H
