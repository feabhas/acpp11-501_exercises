// SevenSegment.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include "GPIO.h"

namespace Devices {

    class SevenSegment {
    public:
        SevenSegment(GPIO& gpio);
        ~SevenSegment();
        void display(unsigned int value);
        void blank();
    private:
        GPIO& gpio;
    };


}  // namespace Devices

#endif // SEVENSEGMENT_H_
