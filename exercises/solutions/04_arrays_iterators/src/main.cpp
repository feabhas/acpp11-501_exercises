// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <cstdint>
#include <array>
#include "Timer.h"
#include "Step.h"

using WMS::Step;

constexpr static unsigned num_steps { 15 };

static std::array<Step, num_steps> colour_wash {
    Step {Step::Type::empty,    500},
    Step {Step::Type::fill,    1000},
    Step {Step::Type::heat,    2000},
    Step {Step::Type::wash,    2500},
    Step {Step::Type::rinse,   2000},
    Step {Step::Type::spin,    3000},
    Step {Step::Type::dry,     2400},
    Step {Step::Type::complete, 500},
};

int main()
{

    for(auto& step: colour_wash){
        if (step.is_valid()) {
            step.run();
        }
    }
    for(auto it=std::begin(colour_wash); it != std::end(colour_wash); ++it) {
        if (it->is_valid()) {
            it->run();
        }
    }
}
