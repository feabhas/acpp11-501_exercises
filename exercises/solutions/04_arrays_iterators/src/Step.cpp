// Step.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include "Timer.h"
#include <iomanip>
#include <iostream>

namespace WMS {
namespace {

constexpr std::size_t num_steps = 9;

static constexpr std::string_view names[num_steps] = {
    "invalid", "empty", "fill", "heat",    "wash",
    "rinse",   "spin",  "dry",  "complete"};
} // namespace

Step::Step(Type step_type, std::uint32_t step_length)
    : type{step_type}, duration{step_length} {}

Step::Type Step::get_type() const { return type; }

std::uint32_t Step::get_duration() const { return duration; }

bool Step::is_valid() const { return type != Type::invalid; }

void Step::run() {
  if (!is_valid()) {
    std::cerr << "Invalid step\n";
    return;
  }
  display();
  sleep(duration);
}

constexpr std::string_view Step::to_string() const {
  return names[unsigned(type)];
}

void Step::display() const {
  std::cout << std::fixed << std::setprecision(2);

  std::cout << "Step " << unsigned(type) << " '" << to_string() << "' ";
  std::cout << "running for " << duration / 1000.0 << " seconds";
  std::cout << '\n';
}

} // namespace WMS
