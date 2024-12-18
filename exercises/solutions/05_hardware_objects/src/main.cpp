// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <cstdint>
#include "GPIO.h"
#include "Timer.h"
#include "Peripherals.h"

static constexpr uint32_t led_A{8};

int main()
{
    Devices::GPIO gpiod {STM32F407::AHB1_Device::GPIO_D};

    for (unsigned pin = led_A; pin <led_A+4; ++pin) {
        gpiod.set_output(pin);
    }

    for (unsigned i = 0; i < 10; ++i) {
        gpiod.clear(0xFU << led_A);
        gpiod.set(i << led_A);
        sleep(500);
    }

    gpiod.set(0xFU << led_A);
    sleep(500);
}
