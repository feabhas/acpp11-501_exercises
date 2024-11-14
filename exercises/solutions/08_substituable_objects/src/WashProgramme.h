// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include <array>

namespace Devices {
    class SevenSegment;
}

namespace WMS {
    class  Step;

    class WashProgramme {
    public:
        WashProgramme() = default;
        bool add(Step& step);
        void run();

        friend void connect(WashProgramme& wp, Devices::SevenSegment& display);

    private:
        constexpr static unsigned num_steps { 16 };
        using container = std::array<Step*, num_steps>;
        container steps { };
        container::iterator next { std::begin(steps) };
        Devices::SevenSegment* sseg {};
    };

}  // namespace WMS

#endif // WASHPROGRAMME_H_
