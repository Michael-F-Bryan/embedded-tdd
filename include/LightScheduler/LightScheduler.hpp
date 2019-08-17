#if !defined(LIGHT_SCHEDULER_H)
#define LIGHT_SCHEDULER_H

#include "LightController.hpp"
#include "time.hpp"
#include <optional>
#include <stdint.h>

namespace light_scheduler {

class LightScheduler {
public:
  LightScheduler();

  void wake_up();
  void turn_on(LightID light_id, Day day, int minute_of_day);
  void turn_off(LightID light_id, Day day, int minute_of_day);
};

} // namespace light_scheduler

#endif // LIGHT_SCHEDULER_H
