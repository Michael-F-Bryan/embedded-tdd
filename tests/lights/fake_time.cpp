#include "fake_time.hpp"
#include "lights/LightScheduler.hpp"

using namespace lights;

static Time now = Time();

namespace lights {

Time get_time() { return now; }

} // namespace lights

namespace fake_time {

void set_day(Day day) { now.day_of_week = day; }

void set_minute(uint16_t minute) { now.minute_of_day = minute; }

} // namespace fake_time
