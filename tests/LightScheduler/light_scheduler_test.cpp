#include "LightScheduler.hpp"
#include "fake_time.hpp"
#include "gtest/gtest.h"

using namespace light_scheduler;

class LightSchedulerTest : public ::testing::Test {};

TEST_F(LightSchedulerTest, schedule_on_everyday_not_time_yet) {
  LightScheduler scheduler;
  fake_time::set_day(Day::Monday);
  fake_time::set_minute(1199);

  scheduler.turn_on(3, Frequency::EveryDay, 1200);
  scheduler.wake_up();

  ASSERT_FALSE(scheduler.last_id());
  ASSERT_EQ(LightState::Unknown, scheduler.last_state());
}