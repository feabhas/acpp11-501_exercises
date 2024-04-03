// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include <array>

namespace Devices {
    class OutputDevice;
}

namespace WMS {
    class  Step;

    class WashProgramme {
    public:
        bool add(Step *const step);
        void run();

        friend void connect(WashProgramme& wp, Devices::OutputDevice& display);

    private:
        constexpr static unsigned num_steps { 16 };
        using container = std::array<Step*, num_steps>;
        container steps { };
        container::iterator next { std::begin(steps) };

        Devices::OutputDevice* output {};
    };

}  // namespace WMS

#endif // WASHPROGRAMME_H_
