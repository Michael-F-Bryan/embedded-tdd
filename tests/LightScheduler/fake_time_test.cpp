#include "LightScheduler/time.hpp"
#include "fake_time.hpp"
#include "gtest/gtest.h"

using namespace light_scheduler;

class FakeTimeTest : public ::testing::Test {};

TEST_F(FakeTimeTest, get_and_set) {
  fake_time::set_day(Day::Saturday);
  fake_time::set_minute(42);

  Time got = get_time();

  Time expected = Time(42, Day::Saturday);
  ASSERT_EQ(expected, got);
}