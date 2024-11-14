// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include "Timer.h"
#include <array>
#include <cstdint>

using WMS::Step;

constexpr static std::size_t num_steps{16};

static std::array<Step, num_steps> colour_wash{
    Step{Step::Type::fill, 1000}, Step{Step::Type::heat, 1200},
    Step{Step::Type::wash, 1500}, Step{Step::Type::empty, 500},
    Step{Step::Type::fill, 1000}, Step{Step::Type::rinse, 2000},
    Step{Step::Type::empty, 500}, Step{Step::Type::spin, 2000},
    Step{Step::Type::dry, 1400},  Step{Step::Type::complete, 500},
};

int main() {
  for (auto &step : colour_wash) {
    step.run();
  }
  for (auto it = std::begin(colour_wash); it != std::end(colour_wash); ++it) {
    it->run();
  }
}
