// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "SerialPort.h"

using Devices::SerialPort;

int main()
{
    SerialPort port{};
    port.send("\r\nType characters. # to terminate\r\n");
    char data{};
    do {
        data = port.get_char();
        port.send(data);
    } while (data != '#');
}

