#include "LedDriver.hpp"

 LedDriver::LedDriver(uint16_t *bits) : m_bits(bits) {
  m_current_state = ALL_LEDS_OFF;
  *m_bits = m_current_state;
}

uint16_t mask_for_bit(int bit) { return 1 << (bit - 1); }

 void LedDriver::turn_on(int bit) {
  if (bit <= 0 || bit > sizeof(uint16_t) * 8) {
    return;
  }

  m_current_state |= mask_for_bit(bit);
  update_hardware();
}

 void LedDriver::turn_off(int bit) {
  m_current_state &= ~mask_for_bit(bit);
  update_hardware();
}

 void LedDriver::all_on() {
  m_current_state = ALL_LEDS_ON;
  update_hardware();
}

 void LedDriver::update_hardware() {
  *m_bits = m_current_state;
}