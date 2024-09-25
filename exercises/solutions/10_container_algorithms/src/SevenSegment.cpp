// SevenSegment.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "SevenSegment.h"

namespace Devices {

enum LED : unsigned { A = 8, B, C, D };

SevenSegment::SevenSegment(GPIO &gpio) : gpio{gpio} {
  gpio.set_output(LED::A);
  gpio.set_output(LED::B);
  gpio.set_output(LED::C);
  gpio.set_output(LED::D);
  blank();
}

SevenSegment::~SevenSegment() { blank(); }

void SevenSegment::display(unsigned value) {
  value &= 0xFu;
  gpio.clear(0xFu << LED::A);
  gpio.set(value << LED::A);
}

void SevenSegment::blank() { display(15); }

} // namespace Devices
