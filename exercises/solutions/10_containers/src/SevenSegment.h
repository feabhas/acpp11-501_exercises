// SevenSegment.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include "GPIO.h"
#include "OutputDevice.h"

namespace Devices {

    class SevenSegment : public OutputDevice {
    public:
        SevenSegment(GPIO& gpio);
        ~SevenSegment() override;
        void display(unsigned int value) override;
        void blank();
    private:
        GPIO& gpio;
    };


}  // namespace Devices

#endif // SEVENSEGMENT_H_
