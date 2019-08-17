#include "fake_light_controller.hpp"
#include "lights/LightController.hpp"
#include "gtest/gtest.h"

class LightControllerTest : public testing::Test {
public:
  LightControllerTest() { fake_light_controller::reset(); }
};

TEST_F(LightControllerTest, remember_all_light_states) {
  lights::turn_on(42);
  lights::turn_off(13);

  ASSERT_EQ(lights::LightState::On, fake_light_controller::last_state(42));
  ASSERT_EQ(lights::LightState::Off, fake_light_controller::last_state(13));
}