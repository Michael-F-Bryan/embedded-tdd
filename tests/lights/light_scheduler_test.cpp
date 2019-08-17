#include "fake_time.hpp"
#include "lights/LightScheduler.hpp"
#include "lights/internal.hpp"
#include "gtest/gtest.h"

using namespace lights;

class LightSchedulerTest : public testing::Test {
public:
  LightSchedulerTest() {
    fake_time::set_time(Day::Monday, 0);
    set_last_id(std::optional<LightID>());
    set_last_state(LightState::Unknown);
  }
};

TEST_F(LightSchedulerTest, nothing_happens_when_nothing_scheduled) {
  LightScheduler scheduler;

  scheduler.wake_up();

  ASSERT_FALSE(last_id());
  ASSERT_EQ(LightState::Unknown, last_state());
}

TEST_F(LightSchedulerTest, schedule_on_everyday_not_time_yet) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Monday, 1199);

  scheduler.turn_on(3, Day::EveryDay, 1200);
  scheduler.wake_up();

  ASSERT_FALSE(last_id());
  ASSERT_EQ(LightState::Unknown, last_state());
}

TEST_F(LightSchedulerTest, schedule_on_everyday_it_is_time) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Monday, 1200);

  scheduler.turn_on(3, Day::Monday, 1200);
  scheduler.wake_up();

  ASSERT_EQ(3, last_id());
  ASSERT_EQ(LightState::On, last_state());
}

TEST_F(LightSchedulerTest, schedule_off_everyday_it_is_time) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Monday, 1200);

  scheduler.turn_off(3, Day::Monday, 1200);
  scheduler.wake_up();

  ASSERT_EQ(3, last_id());
  ASSERT_EQ(LightState::Off, last_state());
}