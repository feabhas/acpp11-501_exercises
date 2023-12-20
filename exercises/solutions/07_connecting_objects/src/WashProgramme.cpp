// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include "WashProgramme.h"
#include "Step.h"
#include "SevenSegment.h"
#include "Timer.h"

namespace WMS {

    bool WashProgramme::add(Step::Type step_type, std::uint32_t duration)
    {
        if (next == std::end(steps)) {
            return false;
        }
        *next = Step{step_type, duration};
        ++next;
        return true;
    }

    void WashProgramme::run()
    {
        for (auto step: steps) {
            if (step.is_valid()) {
                std::cout << "Wash step " << unsigned(step.get_type()) << '\n';
                if (sseg) {
                    sseg->display(unsigned(step.get_type()));
                }
                step.run();
            }
        }
    }

    void connect(WashProgramme& wp, Devices::SevenSegment& display)
    {
        wp.sseg = &display;
    }

}  // namespace WMS
