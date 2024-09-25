// Motor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Motor.h"

namespace Devices {

enum Pin : unsigned { on = 12, dir };

Motor::Motor(GPIO &gpio) : gpio{gpio} {
  gpio.set_output(Pin::on);
  gpio.set_output(Pin::dir);
  off();
}

Motor::~Motor() { off(); }

void Motor::on() { gpio.set(0x1u << Pin::on); }

void Motor::off() { gpio.clear(0x1u << Pin::on); }

void Motor::change_direction() {
  constexpr unsigned mask{0x1u << Pin::dir};
  if ((gpio.read() & mask) != 0) {
    gpio.clear(mask);
  } else {
    gpio.set(mask);
  }
}

} // namespace Devices
