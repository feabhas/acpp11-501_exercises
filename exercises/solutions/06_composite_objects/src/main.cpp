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
  colour_wash.add(Step::Type::heat, 2000);
  colour_wash.add(Step::Type::wash, 2500);
  colour_wash.add(Step::Type::empty, 500);
  colour_wash.add(Step::Type::fill, 1000);
  colour_wash.add(Step::Type::rinse, 2000);
  colour_wash.add(Step::Type::empty, 500);
  colour_wash.add(Step::Type::spin, 3000);
  colour_wash.add(Step::Type::dry, 2400);
  colour_wash.add(Step::Type::complete, 500);

  colour_wash.run();
}
