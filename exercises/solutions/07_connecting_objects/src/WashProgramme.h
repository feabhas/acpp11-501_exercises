// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd
#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include "Step.h"
#include <array>

namespace Devices {
class SevenSegment;
}

namespace WMS {

class WashProgramme {
public:
  WashProgramme() = default;
  bool add(Step::Type step_type, std::uint32_t duration);
  void run();

  friend void connect(WashProgramme &wp, Devices::SevenSegment &display);

private:
  constexpr static std::size_t num_steps{16};
  using container = std::array<Step, num_steps>;
  container steps{};
  container::iterator next{std::begin(steps)};
  Devices::SevenSegment *sseg{};
};

} // namespace WMS

#endif // WASHPROGRAMME_H_
