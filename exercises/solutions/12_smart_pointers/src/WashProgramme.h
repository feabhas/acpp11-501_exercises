// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include <vector>
#include <memory>

namespace Devices {
    class OutputDevice;
}

namespace WMS {

    class Step;

    class WashProgramme {
    public:
        WashProgramme();
        WashProgramme(std::initializer_list<std::shared_ptr<Step>> step_list);

        bool add(std::shared_ptr<Step>);
        void run();
        uint32_t duration();

        friend void connect(WashProgramme& wp, Devices::OutputDevice& display);

    private:
        using container = std::vector<std::shared_ptr<Step>>;
        container steps { };
        Devices::OutputDevice* output {};
    };

}  // namespace WMS

#endif // WASHPROGRAMME_H_
