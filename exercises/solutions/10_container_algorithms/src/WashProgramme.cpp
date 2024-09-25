// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashProgramme.h"
#include "OutputDevice.h"
#include "Step.h"
#include "Timer.h"
#include <iostream>
#include <numeric>

namespace WMS {

WashProgramme::WashProgramme() { steps.reserve(16); }

bool WashProgramme::add(Step &step) {
  steps.push_back(&step);
  return true;
}

void WashProgramme::run() {
  for (auto step : steps) {
    std::cout << "Wash step " << unsigned(step->get_type()) << '\n';
    if (output) {
      output->display(unsigned(step->get_type()));
    }
    step->run();
  }
}

std::uint32_t WashProgramme::duration() {
  return std::accumulate(std::begin(steps), std::end(steps), 0u,
                         [](auto sum, auto step) -> std::uint32_t {
                           return sum + step->get_duration();
                         });
}

void connect(WashProgramme &wp, Devices::OutputDevice &display) {
  wp.output = &display;
}

} // namespace WMS
