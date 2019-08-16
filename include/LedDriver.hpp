#include <cstdint>

class LedDriver {
public:
  LedDriver(uint16_t *bits);

  void turn_on(int bit);
  void turn_off(int bit);
  void all_on();

private:
  const uint16_t ALL_LEDS_ON = ~0;
  const uint16_t ALL_LEDS_OFF = ~LedDriver::ALL_LEDS_ON;

  uint16_t *m_bits;
  uint16_t m_current_state;

  void update_hardware();
};