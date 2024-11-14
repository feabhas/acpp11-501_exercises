// SevenSegment.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "SevenSegment.h"

namespace Devices {

    enum class LED {A=8, B, C, D};

    SevenSegment::SevenSegment(GPIO& gpio)
    : gpio{gpio}
    {
        for (unsigned pin = static_cast<unsigned>(LED::A); pin <= static_cast<unsigned>(LED::D); ++pin) {
            gpio.set_output(pin);
        }
        blank();
    }


    SevenSegment::~SevenSegment()
    {
        blank();
    }


    void SevenSegment::display(unsigned value)
    {
        if (value > 0xFU) return;
        gpio.clear(0xFU << static_cast<unsigned>(LED::A));
        gpio.set(value << static_cast<unsigned>(LED::A));
    }


    void SevenSegment::blank()
    {
        display(0xFU);
    }

}  // namespace Devices
