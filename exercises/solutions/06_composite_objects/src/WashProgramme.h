// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include <array>
#include "Step.h"

namespace WMS {

    class WashProgramme {
    public:
        WashProgramme() = default;
        bool add(Step::Type step_type, std::uint32_t duration);
        void run();

    private:
        constexpr static unsigned num_steps { 16 };
        using container = std::array<Step, num_steps>;
        container steps { };
        container::iterator next { std::begin(steps) };
    };

}  // namespace WMS

#endif // WASHPROGRAMME_H_
