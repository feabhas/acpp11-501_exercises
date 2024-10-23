// SerialPort.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string_view>
#include <optional>
#include "Buffer.h"
#include "USART.h"

namespace Devices
{
    struct UsartStatus;
    union  UsartData;

    class SerialPort : public STM32F407::USART
    {
    public:
        SerialPort();
        static void rx_isr();
        bool try_get(char& chr) override;

    private:
        Utility::Buffer<char> buffer;
        static inline SerialPort *self {};
    };
}


#endif
