#ifndef FAKE_TIME_H
#define FAKE_TIME_H

#include "lights/LightScheduler.hpp"

namespace fake_time {

void set_day(lights::Day day);
void set_minute(uint16_t minute);

inline void set_time(lights::Day day, uint16_t minute) {
    set_day(day);
    set_minute(minute);
}

} // namespace fake_time

#endif // FAKE_TIME_H
