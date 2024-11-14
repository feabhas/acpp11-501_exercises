// GPIO.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Memory_map.h"
#include <cstdint>

namespace Devices {
struct Registers {
  uint32_t mode;
  uint32_t output_type;
  uint32_t output_speed;
  uint32_t pull_up_down;
  uint32_t input;
  uint32_t output;
  uint32_t bit_set_reset;
  uint32_t lock;
  uint32_t alt_fn_low;
  uint32_t alt_fn_high;
};

static_assert(sizeof(Registers) == 40, "Register map incorrect");

GPIO::GPIO(STM32F407::AHB1_Device device)
    : device{device}, port{reinterpret_cast<Registers *>(
                          STM32F407::device_base_address(device))} {
  STM32F407::enable(device);
}

GPIO::~GPIO() { STM32F407::disable(device); }

void GPIO::set_input(unsigned pin) {
  if (pin > 15)
    return;
  port->mode &= ~(0x3U << pin * 2);
  // C++20 only
  // auto moder = port->mode;
  // moder &= ~(0x3U << pin*2);
  // port->mode = moder;
}

void GPIO::set_output(unsigned pin) {
  if (pin > 15)
    return;
  auto moder = port->mode;
  moder &= ~(0x3U << pin * 2);
  moder |= (0x1U << pin * 2);
  port->mode = moder;
}

void GPIO::set(uint32_t pattern) {
  pattern &= 0xFFFF;
  port->output |= pattern;
}

void GPIO::clear(uint32_t pattern) {
  pattern &= 0xFFFF;
  port->output &= ~pattern;
}

uint32_t GPIO::mode() const { return port->mode; }

uint32_t GPIO::read() const { return port->input & 0xFFFF; }

} // namespace Devices
