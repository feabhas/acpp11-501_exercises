// GPIO.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <cstdint>
#include <iostream>
#include <utility>
#include "GPIO.h"
#include "Memory_map.h"

namespace Devices {
    struct Registers {
        uint32_t mode;
        uint32_t output_type;
        uint32_t output_speed;
        uint32_t pull_up_down;
        uint32_t input;
        uint32_t output;
        // not used
        // uint32_t bit_set_reset;
        // uint32_t lock;
        // uint32_t alt_fn_low;
        // uint32_t alt_fn_high;
    };

    GPIO::GPIO(STM32F407::AHB1_Device device)
    : device{device},
      port { reinterpret_cast<Registers*>(STM32F407::device_base_address(device)) }
    {
        STM32F407::enable(device);
        std::cout << "GPIO ctr - enabled" << '\n';
    }

    GPIO::~GPIO()
    {
        if (port) {
            STM32F407::disable(device);
            std::cout << "GPIO dtr - disabled" << '\n';
        }
        else {
            std::cout << "GPIO dtr - empty" << '\n';
        }
    }

    GPIO::GPIO(GPIO&& rhs) noexcept
    : device{rhs.device}, port{std::exchange(rhs.port, nullptr)}
    {
        std::cout << "GPIO move ctr" << '\n';
    }

    GPIO& GPIO::operator=(GPIO&& rhs) noexcept
    {
        std::cout << "GPIO move = ";
        GPIO temp {std::move(rhs)};
        swap(*this, temp);
        return *this;
    }

    void swap(GPIO& lhs, GPIO& rhs)
    {
        using std::swap;
        swap(lhs.device, rhs.device);
        swap(lhs.port, rhs.port);
    }

    void GPIO::set_input(unsigned pin)
    {
        port->mode &= ~(0x3u << pin*2);
        // C++20 only
        // auto moder = port->mode;
        // moder &= ~(0x3u << pin*2);
        // port->mode = moder;
    }

    void GPIO::set_output(unsigned pin)
    {
        auto moder = port->mode;
        moder &= ~(0x3u << pin*2);
        moder |= (0x1u << pin*2);
        port->mode = moder;
    }

    void GPIO::set(uint32_t pattern)
    {
        port->output |= pattern;
        // C++20 only
        // uint32_t value = port->output;
        // value |= pattern;
        // port->output = value;
    }

    void GPIO::clear(uint32_t pattern)
    {
        port->output &= ~pattern;
        // C++20 only
        // uint32_t value = port->output;
        // value &= ~pattern;
        // port->output = value;
    }

    uint32_t GPIO::mode() const
    {
        return port->mode;
    }

    uint32_t GPIO::read() const
    {
        return port->input;
    }


} // namespace STM32F407
