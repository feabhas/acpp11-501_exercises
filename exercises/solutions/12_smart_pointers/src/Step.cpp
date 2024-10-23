// Step.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include "Timer.h"
#include <iomanip>
#include <iostream>

namespace WMS
{
  namespace {
    static constexpr std::string_view names[9] = {
      "invalid", "empty", "fill",
      "heat",    "wash",  "rinse",
      "spin",    "dry",   "complete"
    };
  }

  Step::Step(Type step_type, uint32_t step_length) :
    type{ step_type }, duration{ step_length }
  {  }

  void Step::run()
  {
    display();
    sleep(duration);
  }

  constexpr std::string_view Step::to_string() const {
    return names[unsigned(type)];
  }

  void Step::display() const
  {
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Step " << int(type) <<  " '" << to_string() << "' ";
    std::cout << "running for " << duration/1000.0 << " seconds";
    std::cout << '\n';
  }

} // namespace WMS
