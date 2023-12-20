// GPIO.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef GPIO_H
#define GPIO_H

#include <cstdint>
#include "Peripherals.h"

namespace Devices {
    class GPIO {
    public:
        explicit GPIO(STM32F407::AHB1_Device device);
        ~GPIO();
        void set_input(unsigned pin);
        void set_output(unsigned pin);
        uint32_t mode() const;
        uint32_t read() const;
        void set(uint32_t pattern);
        void clear(uint32_t pattern);
    private:
        STM32F407::AHB1_Device device {};
        volatile struct Registers* port {};
    };


} // namespace Devices

#endif // GPIO_H_
