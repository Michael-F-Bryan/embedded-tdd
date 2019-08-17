#if !defined(LIGHT_SCHEDULER_H)
#define LIGHT_SCHEDULER_H

#include <optional>
#include <stdint.h>

namespace light_scheduler {

enum class Frequency {
  EveryDay,
};

enum class Day {
  Monday,
};

enum class LightState {
  Unknown,
};

class LightScheduler {
public:
  using LightID = uint16_t;

  LightScheduler();

  void wake_up();
  void turn_on(LightID light_id, Frequency frequency, uint16_t time);
};

} // namespace light_scheduler

#endif // LIGHT_SCHEDULER_H
