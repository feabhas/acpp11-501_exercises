// Step.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include "Timer.h"
#include <iomanip>
#include <iostream>
namespace {
static constexpr const char *names[] = {"invalid", "empty", "fill",
                                        "heat",    "wash",  "rinse",
                                        "spin",    "dry",   "complete"};
}

namespace WMS {
Step::Step(Type step_type, uint32_t step_length)
    : type{step_type}, duration{step_length} {}

Step::Type Step::get_type() const { return type; }

uint32_t Step::get_duration() const { return duration; }

bool Step::is_valid() const { return type != Type::invalid; }

void Step::run() {
  if (!is_valid()) {
    // std::cerr << "Invalid step\n";
    return;
  }
  display();
  sleep(duration);
}

const char *Step::to_string() const { return names[unsigned(type)]; }

void Step::display() const {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Step " << int(type) << " '" << to_string() << "' ";
  std::cout << "running for " << duration / 1000.0 << " seconds";
  std::cout << '\n';
}

} // namespace WMS
