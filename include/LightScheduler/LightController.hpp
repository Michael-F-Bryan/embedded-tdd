#if !defined(LIGHT_CONTROLLER_H)
#define LIGHT_CONTROLLER_H

#include <stdint.h>

namespace light_scheduler {

using LightID = uint16_t;

void turn_on(LightID id);
void turn_off(LightID id);

} // namespace light_scheduler

#endif // LIGHT_CONTROLLER_H
