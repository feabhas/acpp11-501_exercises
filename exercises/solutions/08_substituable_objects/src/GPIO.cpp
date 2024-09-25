// GPIO.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Memory_map.h"
#include <cstdint>

namespace Devices {
struct Registers {
  volatile std::uint32_t mode;
  volatile std::uint32_t output_type;
  volatile std::uint32_t output_speed;
  volatile std::uint32_t pull_up_down;
  volatile std::uint32_t input;
  volatile std::uint32_t output;
  volatile std::uint32_t bit_set_reset;
  volatile std::uint32_t lock;
  volatile std::uint32_t alt_fn_low;
  volatile std::uint32_t alt_fn_high;
};

GPIO::GPIO(STM32F407::AHB1_Device device)
    : device{device}, port{reinterpret_cast<Registers *>(
                          STM32F407::device_base_address(device))} {
  STM32F407::enable(device);
}

GPIO::~GPIO() {
  port->mode = 0;
  STM32F407::disable(device);
}

void GPIO::set_input(unsigned pin) {
  if (pin > 15)
    return;
  port->mode &= ~(0x3u << pin * 2);
  // C++20 only
  // auto moder = port->mode;
  // moder &= ~(0x3u << pin*2);
  // port->mode = moder;
}

void GPIO::set_output(unsigned pin) {
  if (pin > 15)
    return;
  auto moder = port->mode;
  moder &= ~(0x3u << pin * 2);
  moder |= (0x1u << pin * 2);
  port->mode = moder;
}

void GPIO::set(std::uint32_t pattern) {
  pattern &= 0xFFFFu;
  port->output |= pattern;
  // C++20 only
  // std::uint32_t value = port->output;
  // value |= pattern;
  // port->output = value;
}

void GPIO::clear(std::uint32_t pattern) {
  pattern &= 0xFFFFu;
  port->output &= ~pattern;
  // C++20 only
  // std::uint32_t value = port->output;
  // value &= ~pattern;
  // port->output = value;
}

std::uint32_t GPIO::mode() const { return port->mode; }

std::uint32_t GPIO::read() const { return (port->input & 0xFFFFu); }

} // namespace Devices
