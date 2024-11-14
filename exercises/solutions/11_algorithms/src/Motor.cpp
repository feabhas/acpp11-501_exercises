// Motor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Motor.h"

namespace Devices {

enum class Pin { on = 12, dir };

Motor::Motor(GPIO &gpio) : gpio{gpio} {
  gpio.set_output(static_cast<unsigned>(Pin::on));
  gpio.set_output(static_cast<unsigned>(Pin::dir));
  off();
}

Motor::~Motor() { off(); }

void Motor::on() { gpio.set(0x1U << static_cast<unsigned>(Pin::on)); }

void Motor::off() { gpio.clear(0x1U << static_cast<unsigned>(Pin::on)); }

void Motor::change_direction() {
  constexpr unsigned mask{0x1U << static_cast<unsigned>(Pin::dir)};
  if (gpio.read() & mask) {
    gpio.clear(mask);
  } else {
    gpio.set(mask);
  }
}

} // namespace Devices
