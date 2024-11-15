#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "GPIO.h"
#include "Timer.h"
#include "Peripherals.h"

TEST_CASE("GPIO Port D configuration") {
    Devices::GPIO gpiod{STM32F407::AHB1_Device::GPIO_D};
    for (unsigned pin = 8; pin < 12; ++pin) {
        gpiod.set_output(pin);
    }    

    SUBCASE("Configure pins as output") {
        // Check mode register - each pin uses 2 bits, output mode is 0x1
        uint32_t expected = 0x550000;  // Pins 8-11 as outputs
        CHECK(gpiod.mode() == expected);
    }

    SUBCASE("Set individual pins") {
        gpiod.set(1U << 8);  // Set pin 8
        CHECK((gpiod.read() & (1U << 8)) != 0);
        
        gpiod.clear(1U << 8);  // Clear pin 8
        CHECK((gpiod.read() & (1U << 8)) == 0);
    }

    SUBCASE("Set multiple pins") {
        uint32_t pattern = 0xFU << 8;  // Pins 8-11
        gpiod.set(pattern);
        CHECK((gpiod.read() & pattern) == pattern);
        
        gpiod.clear(pattern);
        CHECK((gpiod.read() & pattern) == 0);
    }
}
