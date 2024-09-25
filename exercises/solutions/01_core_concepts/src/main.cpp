// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include "Timer.h"
#include <string_view>

enum class StepType { invalid, empty, fill, heat, wash, rinse, spin, dry, complete };

constexpr std::size_t num_steps = 9;

static constexpr std::string_view names[num_steps] = {
    "invalid", "empty", "fill",
    "heat",    "wash",  "rinse",
    "spin",    "dry",   "complete"
};

static constexpr std::string_view to_string(StepType step) {
    return names[int(step)];
}

int main()
{
  for(int i=0; i<5; ++i) {
    std::cout << "Tick..." << '\n';
    sleep(500);
  }
  auto step1 {StepType::empty};
  auto step2 {StepType::fill};
  std::cout << "step1 " <<  int(step1) << " is " << to_string(step1) << '\n';
  std::cout << "step2 " <<  int(step2) << " is " << to_string(step2) << '\n';
}


