// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include "Timer.h"
#include <array>
#include <cstdint>
#include <iostream>

using WMS::Step;

constexpr static std::size_t num_steps{16};

static std::array<Step, num_steps> colour_wash{
    Step{Step::Type::fill, 1000}, Step{Step::Type::heat, 2000},
    Step{Step::Type::wash, 2500}, Step{Step::Type::empty, 500},
    Step{Step::Type::fill, 1000}, Step{Step::Type::rinse, 2000},
    Step{Step::Type::empty, 500}, Step{Step::Type::spin, 3000},
    Step{Step::Type::dry, 2400},  Step{Step::Type::complete, 500},
};

int main() {
  std::cout << "Range-for loop\n";
  for (auto &step : colour_wash) {
    if (step.is_valid()) {
      step.run();
    }
  }

  std::cout << "Iterator-for loop\n";
  for (auto it = std::begin(colour_wash); it != std::end(colour_wash); ++it) {
    if (it->is_valid()) {
      it->run();
    }
  }
}
