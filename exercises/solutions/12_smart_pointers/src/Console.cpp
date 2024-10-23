// Console.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Console.h"
#include <iostream>

namespace Devices {

void Console::display(unsigned int value)
{
  std::cout << "running Step " << value << '\n';
}

} // namespace
