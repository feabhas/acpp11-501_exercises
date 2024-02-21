// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <cstdint>
#include "Peripherals.h"
#include "Timer.h"

constexpr uintptr_t GPIOD_BASE {0x40020C00u};

static volatile uint32_t *const GPIOD_moder {reinterpret_cast<uint32_t*>(GPIOD_BASE)};
static volatile uint32_t *const GPIOD_outr {reinterpret_cast<uint32_t*>(GPIOD_BASE + 0x14u)};
static volatile const uint32_t *const GPIOD_inr {reinterpret_cast<uint32_t*>(GPIOD_BASE + 0x10u)};

enum class LED { A=8, B, C, D };
enum class Motor { on=12, dir };

int main(void)
{
    STM32F407::enable(STM32F407::AHB1_Device::GPIO_D);

    uint32_t moder = *GPIOD_moder;
    moder &= ~(0x3u << int(LED::A)* 2);
    moder |= 0x1u << int(LED::A) * 2;
    *GPIOD_moder = moder;

    for(int i=0; i<5; ++i) {
        puts("tick....");
        uint32_t outr = *GPIOD_outr;
        outr |= 0x1u << static_cast<int>(LED::A);       // prior to C++17
        *GPIOD_outr = outr;
        sleep(500);
        outr &= ~(0x1u << static_cast<int>(LED::A));    // prior to C++17
        *GPIOD_outr = outr;
        sleep(500);
     }

    moder = *GPIOD_moder;
    moder &= ~(0xFu << int(Motor::on)* 2);
    moder |= 0x5u << int(Motor::on) * 2;
    *GPIOD_moder = moder;

    for(int i=0; i<5; ++i) {
        puts("spin....");
        uint32_t outr = *GPIOD_outr;
        outr ^= 0x1u << int(Motor::dir);
        outr |= 0x1u << int(Motor::on);
        *GPIOD_outr = outr;
        sleep(500);
        outr &= ~(0x1u << int(Motor::on));
        *GPIOD_outr = outr;
        sleep(500);
     }

    moder = *GPIOD_moder;
    moder &= ~(0xFFu << int(LED::A)* 2);
    moder |= 0x55u << int(LED::A) * 2;
    *GPIOD_moder = moder;

    for(unsigned i=0; i<10; ++i) {
        puts("count....");
        uint32_t outr = *GPIOD_outr;
        outr &= ~(0xFu << int(LED::A));
        outr |= i << int(LED::A);
        *GPIOD_outr = outr;
        sleep(500);
     }
}
