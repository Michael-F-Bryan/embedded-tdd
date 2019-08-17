#include "LedDriver.hpp"
#include <stdexcept>
#include <string>

uint16_t mask_for_bit(int bit) { return 1 << (bit - 1); }

void LedDriver::bounds_check(int bit) {
  if (bit <= 0 || bit > sizeof(uint16_t) * 8) {
    std::string message;
    message += "Bit ";
    message += bit;
    message += " is out of bounds";

    throw std::invalid_argument(message);
  }
}

void LedDriver::set_bit(int bit) {
  bounds_check(bit);

  m_current_state |= mask_for_bit(bit);
}

void LedDriver::clear_bit(int bit) {
  bounds_check(bit);

  m_current_state &= ~mask_for_bit(bit);
}

LedDriver::LedDriver(uint16_t *bits) : m_bits(bits) {
  m_current_state = ALL_LEDS_OFF;
  *m_bits = m_current_state;
}

void LedDriver::turn_on(int bit) {
  set_bit(bit);
  update_hardware();
}

void LedDriver::turn_off(int bit) {
  clear_bit(bit);
  update_hardware();
}

void LedDriver::all_on() {
  m_current_state = ALL_LEDS_ON;
  update_hardware();
}

void LedDriver::update_hardware() { *m_bits = m_current_state; }