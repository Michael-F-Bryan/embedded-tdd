#include <iostream>

#include "LedDriver.hpp"
#include "gtest/gtest.h"

class LedDriverTest : public ::testing::Test {};

TEST_F(LedDriverTest, leds_are_off_after_create) {
  uint16_t bits = 0xffff;
  LedDriver driver(&bits);

  ASSERT_EQ(0, bits);
}

TEST_F(LedDriverTest, activate_first_led) {
  uint16_t bits;
  LedDriver driver(&bits);

  driver.turn_on(1);

  ASSERT_EQ(1, bits);
}

TEST_F(LedDriverTest, toggle_first_led) {
  uint16_t bits;
  LedDriver driver(&bits);

  driver.turn_on(1);
  driver.turn_off(1);

  ASSERT_EQ(0, bits);
}

TEST_F(LedDriverTest, turn_on_multiple_leds) {
  uint16_t bits;
  LedDriver driver(&bits);

  driver.turn_on(9);
  driver.turn_on(8);

  ASSERT_EQ(0x180, bits);
}

TEST_F(LedDriverTest, turn_off_any_led) {
  uint16_t bits;
  LedDriver driver(&bits);
  driver.all_on();

  driver.turn_off(8);

  ASSERT_EQ(0xff7f, bits);
}

TEST_F(LedDriverTest, all_on) {
  uint16_t bits;
  LedDriver driver(&bits);

  driver.all_on();

  ASSERT_EQ(0xffff, bits);
}

TEST_F(LedDriverTest, led_memory_is_never_read) {
  uint16_t bits;
  LedDriver driver(&bits);
  bits = 0xffff;

  driver.turn_on(8);

  ASSERT_EQ(0x0080, bits);
}

TEST_F(LedDriverTest, upper_and_lower_bounds) {
  uint16_t bits;
  LedDriver driver(&bits);

  driver.turn_on(1);
  driver.turn_on(16);

  ASSERT_EQ(0x8001, bits);
}

TEST_F(LedDriverTest, cant_turn_on_out_of_bounds_leds) {
  uint16_t bits;
  LedDriver driver(&bits);

  driver.turn_on(-1);
  driver.turn_on(0);
  driver.turn_on(17);
  driver.turn_on(3141);

  ASSERT_EQ(0, bits);
}

TEST_F(LedDriverTest, cant_turn_off_out_of_bounds_leds) {
  uint16_t bits = 0xffff;
  LedDriver driver(&bits);

  driver.turn_off(-1);
  driver.turn_off(0);
  driver.turn_off(17);
  driver.turn_off(3141);

  ASSERT_EQ(0, bits);
}