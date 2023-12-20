// SerialPort.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include "USART_utils.h"
#include "Peripherals.h"
#include "stm32f407xx.h"
#include "SerialPort.h"

using Devices::SerialPort;


extern "C" void USART3_IRQHandler(void)
{
    SerialPort::rx_isr();
}

namespace Devices
{

     SerialPort::SerialPort()
    {
        self = this;
        USART::enable_rx_interrupt();
        NVIC_EnableIRQ(USART3_IRQn);
        NVIC_SetPriority(USART3_IRQn, 10);
    }

    bool SerialPort::try_get(char& chr)
    {
        NVIC_DisableIRQ(USART3_IRQn);
        auto data = buffer.get();
        NVIC_EnableIRQ(USART3_IRQn);
        if (data.has_value()) {
            chr = *data;
        }
        return data.has_value();
    }

    void SerialPort::rx_isr()
    {
        char data{};
        if (self->USART::try_get(data)) {
            self->buffer.add(data);
        }
    }
}
