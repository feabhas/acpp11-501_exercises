// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <numeric>
#include <iterator>
#include "Step.h"
#include "WashProgramme.h"
#include "OutputDevice.h"

namespace WMS {

    WashProgramme::WashProgramme()
    {
        steps.reserve(16);
    }

    WashProgramme::WashProgramme(std::initializer_list<std::shared_ptr<Step>> step_list)
        : steps{step_list}
    {
    }

    bool WashProgramme::add(std::shared_ptr<Step> step)
    {
        steps.push_back(step);
        return true;
    }

    void WashProgramme::run()
    {
        for (auto& step: steps) {;
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
            [] (uint32_t sum, auto& step) -> uint32_t {return sum + step->get_duration(); } );
    }

    void connect(WashProgramme& wp, Devices::OutputDevice& display)
    {
        wp.output = &display;
    }


}  // namespace WMS
