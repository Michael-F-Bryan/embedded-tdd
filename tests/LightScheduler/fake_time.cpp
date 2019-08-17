#include "fake_time.hpp"
#include "LightScheduler.hpp"

using namespace light_scheduler;

static Time now = Time();

Time light_scheduler::get_time() { return now; }

void fake_time::set_day(Day day) { now.day_of_week = day; }

void fake_time::set_minute(uint16_t minute) { now.minute_of_day = minute; }