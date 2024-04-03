// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <numeric>
#include "WashProgramme.h"
#include "Step.h"
#include "OutputDevice.h"
#include "Timer.h"

namespace WMS {

    WashProgramme::WashProgramme()
    {
        steps.reserve(16);
    }

    bool WashProgramme::add(Step *const step)
    {
        steps.push_back(step);
        return true;
    }

    void WashProgramme::run()
    {
        for (auto step: steps) {;
            std::cout << "Wash step " << unsigned(step->get_type()) << '\n';
            if (output) {
                output->display(unsigned(step->get_type()));
            }
            step->run();
        }
    }

    uint32_t WashProgramme::duration()
    {
        return std::accumulate(std::begin(steps), std::end(steps), 0u,
            [] (uint32_t sum, const Step *const step) -> uint32_t {return sum + step->get_duration(); } );
    }

    void connect(WashProgramme& wp, Devices::OutputDevice& display)
    {
        wp.output = &display;
    }

}  // namespace WMS
