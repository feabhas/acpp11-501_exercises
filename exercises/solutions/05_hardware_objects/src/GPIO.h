// GPIO.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd
#ifndef GPIO_H
#define GPIO_H

#include "Peripherals.h"
#include <cstdint>

namespace Devices {

class GPIO {
public:
  explicit GPIO(STM32F407::AHB1_Device device);
  ~GPIO();
  void set_input(unsigned pin);
  void set_output(unsigned pin);
  std::uint32_t mode() const;
  std::uint32_t read() const;
  void set(std::uint32_t pattern);
  void clear(std::uint32_t pattern);

private:
  STM32F407::AHB1_Device device{};
  struct Registers *port{};
};

} // namespace Devices

#endif // GPIO_H_
