// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <cstdint>
#include "GPIO.h"
#include "Timer.h"
#include "WashProgramme.h"

using WMS::Step;

int main()
{

    WMS::WashProgramme white_wash{};
    white_wash.add(Step::Type::empty,    500);
    white_wash.add(Step::Type::fill,    1000);
    white_wash.add(Step::Type::heat,    2000);
    white_wash.add(Step::Type::wash,    2500);
    white_wash.add(Step::Type::rinse,   2000);
    white_wash.add(Step::Type::spin,    3000);
    white_wash.add(Step::Type::dry,     2400);
    white_wash.add(Step::Type::complete, 500);

    white_wash.run();
}
