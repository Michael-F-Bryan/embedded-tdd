#include "fake_light_controller.hpp"
#include "fake_time.hpp"
#include "lights/LightScheduler.hpp"
#include "gtest/gtest.h"
#include <memory>

using namespace lights;
using namespace fake_light_controller;

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

  scheduler.turn_on(3, Day::EveryDay, 1200);
  scheduler.wake_up();

  ASSERT_TRUE(last_id().has_value());
  ASSERT_EQ(3, last_id());
  ASSERT_EQ(LightState::On, last_state());
}

TEST_F(LightSchedulerTest, schedule_off_everyday_it_is_time) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Monday, 1200);

  scheduler.turn_off(3, Day::EveryDay, 1200);
  scheduler.wake_up();

  ASSERT_TRUE(last_id().has_value());
  ASSERT_EQ(3, last_id());
  ASSERT_EQ(LightState::Off, last_state());
}

TEST_F(LightSchedulerTest, scheduled_for_tuesday_but_its_monday) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Monday, 1200);

  scheduler.turn_off(3, Day::Tuesday, 1200);
  scheduler.wake_up();

  ASSERT_FALSE(last_id().has_value());
  ASSERT_EQ(LightState::Unknown, last_state());
}

TEST_F(LightSchedulerTest, scheduled_for_tuesday_and_its_tuesday) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Tuesday, 1200);

  scheduler.turn_off(3, Day::Tuesday, 1200);
  scheduler.wake_up();

  ASSERT_TRUE(last_id().has_value());
  ASSERT_EQ(3, last_id());
  ASSERT_EQ(LightState::Off, last_state());
}

TEST_F(LightSchedulerTest, scheduled_for_weekend_its_friday) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Friday, 1200);

  scheduler.turn_off(3, Day::Weekend, 1200);
  scheduler.wake_up();

  ASSERT_FALSE(last_id().has_value());
  ASSERT_EQ(LightState::Unknown, last_state());
}

TEST_F(LightSchedulerTest, scheduled_for_weekend_its_saturday) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Saturday, 1200);

  scheduler.turn_off(3, Day::Weekend, 1200);
  scheduler.wake_up();

  ASSERT_TRUE(last_id().has_value());
  ASSERT_EQ(3, last_id());
  ASSERT_EQ(LightState::Off, last_state());
}

TEST_F(LightSchedulerTest, scheduled_for_weekend_its_sunday) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Sunday, 1200);

  scheduler.turn_off(3, Day::Weekend, 1200);
  scheduler.wake_up();

  ASSERT_TRUE(last_id().has_value());
  ASSERT_EQ(3, last_id());
  ASSERT_EQ(LightState::Off, last_state());
}

TEST_F(LightSchedulerTest, scheduled_for_weekend_its_monday) {
  LightScheduler scheduler;
  fake_time::set_time(Day::Monday, 1200);

  scheduler.turn_off(3, Day::Weekend, 1200);
  scheduler.wake_up();

  ASSERT_FALSE(last_id().has_value());
  ASSERT_EQ(LightState::Unknown, last_state());
}

class LightSchedulerInitAndCleanup : public testing::Test {};

TEST_F(LightSchedulerInitAndCleanup, register_scheduler_wake_up) {
  auto scheduler = std::make_shared<LightScheduler>();

  AlarmID id = register_wakeup(60, scheduler);

  auto alarm_period = fake_time::get_alarm_period();
  ASSERT_TRUE(alarm_period.has_value());
  ASSERT_EQ(60, alarm_period);
  ASSERT_TRUE(fake_time::next_callback().has_value());
}

TEST_F(LightSchedulerInitAndCleanup, clear_scheduler_wakeup) {
  auto scheduler = std::make_shared<LightScheduler>();
  AlarmID id = register_wakeup(60, scheduler);

  cancel_periodic_alarm(id);

  ASSERT_FALSE(fake_time::get_alarm_period().has_value());
  ASSERT_FALSE(fake_time::next_callback().has_value());
}