#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H

#include "LightController.hpp"
#include "time.hpp"
#include <memory>
#include <optional>
#include <stdint.h>

namespace lights {

class LightScheduler {
public:
  LightScheduler();

  void wake_up();
  void turn_on(LightID light_id, Day day, int minute_of_day);
  void turn_off(LightID light_id, Day day, int minute_of_day);
};

AlarmID register_wakeup(int seconds,
                        std::shared_ptr<LightScheduler> &scheduler);

} // namespace lights

#endif // LIGHT_SCHEDULER_H
