// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Timer.h"
#include "WashProgramme.h"
#include <cstdint>

using WMS::Step;

int main() {

  WMS::WashProgramme colour_wash{};

  colour_wash.add(Step::Type::fill, 1000);
  colour_wash.add(Step::Type::heat, 1200);
  colour_wash.add(Step::Type::wash, 1500);
  colour_wash.add(Step::Type::empty, 500);
  colour_wash.add(Step::Type::fill, 1000);
  colour_wash.add(Step::Type::rinse, 2000);
  colour_wash.add(Step::Type::empty, 500);
  colour_wash.add(Step::Type::spin, 2000);
  colour_wash.add(Step::Type::dry, 1400);
  colour_wash.add(Step::Type::complete, 500);

  colour_wash.run();
}
