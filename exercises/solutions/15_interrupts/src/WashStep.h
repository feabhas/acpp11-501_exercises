// WashStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
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

        std::unique_ptr<Step> clone() const override {
            return std::make_unique<WashStep>(*this);
        }

        void run() override;

    private:
        Devices::Motor* motor { nullptr };
    };

}  // namespace WMS

#endif // WASHSTEP_H_
