#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <iostream>
#include <stdint.h>

namespace lights {

using LightID = uint16_t;

void turn_on(LightID id);
void turn_off(LightID id);

enum class LightState {
  On,
  Off,
};

inline std::ostream &operator<<(std::ostream &outs, const LightState &state) {
  switch (state) {
  case LightState::Off:
    return outs << "Off";
  case LightState::On:
    return outs << "On";
  default:
    return outs << "<unknown state>";
  }
}

} // namespace lights

#endif // LIGHT_CONTROLLER_H
