#include "fake_time.hpp"
#include "LightScheduler.hpp"

using namespace light_scheduler;

static Time now = Time();

namespace fake_time {

void set_day(Day day) { now.day_of_week = day; }

void set_minute(uint16_t minute) { now.minute_of_day = minute; }

}

namespace light_scheduler {

Time get_time() { return now; }

}
