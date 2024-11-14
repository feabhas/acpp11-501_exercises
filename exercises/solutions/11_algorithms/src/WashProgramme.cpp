// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashProgramme.h"
#include "SevenSegment.h"
#include "Step.h"
#include "Timer.h"
#include <iostream>
#include <numeric>

namespace WMS {

WashProgramme::WashProgramme(std::initializer_list<Step *> step_list) {
  for (auto step : step_list) {
    add(*step);
  }
}

bool WashProgramme::add(Step &step) {
  steps.push_back(&step);
  return true;
}

void WashProgramme::run() {
  for (auto step : steps) {
    std::cout << "Wash step " << unsigned(step->get_type()) << '\n';
    if (sseg) {
      sseg->display(unsigned(step->get_type()));
    }
    step->run();
  }
}

uint32_t WashProgramme::duration() {
  return std::accumulate(std::begin(steps), std::end(steps), 0U,
                         [](uint32_t sum, auto step) -> uint32_t {
                           return sum + step->get_duration();
                         });
}

void connect(WashProgramme &wp, Devices::SevenSegment &display) {
  wp.sseg = &display;
}

} // namespace WMS