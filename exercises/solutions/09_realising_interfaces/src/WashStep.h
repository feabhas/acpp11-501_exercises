// WashStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef WASHSTEP_H
#define WASHSTEP_H

#include "Step.h"

namespace Devices {
    class Motor;
}

namespace WMS {

    class WashStep : public Step {
    public:
        WashStep(Type step_type, std::uint32_t duration, Devices::Motor& motor);

        void run() override;

    private:
        Devices::Motor* motor { nullptr };
    };

}  // namespace WMS

#endif // WASHSTEP_H_
