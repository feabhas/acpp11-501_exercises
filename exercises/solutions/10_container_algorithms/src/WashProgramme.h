// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd
#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include <cstdint>
#include <vector>

namespace Devices {
class OutputDevice;
}

namespace WMS {
class Step;

class WashProgramme {
public:
  WashProgramme();
  bool add(Step &step);
  void run();
  std::uint32_t duration();

  friend void connect(WashProgramme &wp, Devices::OutputDevice &display);

private:
  using container = std::vector<Step *>;
  container steps{};
  Devices::OutputDevice *output{};
};

} // namespace WMS

#endif // WASHPROGRAMME_H_
