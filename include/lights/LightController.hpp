#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <stdint.h>

namespace lights {

using LightID = uint16_t;

void turn_on(LightID id);
void turn_off(LightID id);

} // namespace lights

#endif // LIGHT_CONTROLLER_H
