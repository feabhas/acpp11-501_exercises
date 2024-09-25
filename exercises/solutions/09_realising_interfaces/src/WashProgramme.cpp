// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashProgramme.h"
#include "OutputDevice.h"
#include "Step.h"
#include "Timer.h"
#include <iostream>

namespace WMS {

bool WashProgramme::add(Step &step) {
  if (next == std::end(steps)) {
    return false;
  }
  *next = &step;
  ++next;
  return true;
}

void WashProgramme::run() {
  for (auto step : steps) {
    if (step) {
      std::cout << "Wash step " << unsigned(step->get_type()) << '\n';
      if (output) {
        output->display(unsigned(step->get_type()));
      }
      step->run();
    }
  }
}

void connect(WashProgramme &wp, Devices::OutputDevice &display) {
  wp.output = &display;
}

} // namespace WMS
