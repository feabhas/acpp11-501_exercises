// Console.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef _CONSOLE_H
#define _CONSOLE_H
#include "OutputDevice.h"

namespace Devices {

class Console : public Devices::OutputDevice {
public:
  Console() = default;
  void display(unsigned int value) override;
};

} // namespace Devices

#endif // Console_H_
