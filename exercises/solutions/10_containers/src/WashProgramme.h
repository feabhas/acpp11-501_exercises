// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include <initializer_list>
#include <vector>

namespace Devices {
class SevenSegment;
}

namespace WMS {
class Step;

class WashProgramme {
public:
  WashProgramme() = default;
  WashProgramme(std::initializer_list<Step *> step_list);
  bool add(Step &step);
  void run();

  friend void connect(WashProgramme &wp, Devices::SevenSegment &display);

private:
  using container = std::vector<Step *>;
  container steps{};
  Devices::SevenSegment *sseg{};
};

} // namespace WMS

#endif // WASHPROGRAMME_H_
