// Motor.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MOTOR_H
#define MOTOR_H

#include "GPIO.h"

namespace Devices
{
    class Motor
    {
    public:
        Motor(GPIO &gpiod);
        ~Motor();

        Motor(const Motor& rhs) = delete;
        Motor& operator=(const Motor& rhs) = delete;

        void on();
        void off();
        void change_direction();

    private:
        GPIO& gpio;
    };
}

#endif // MOTOR_H_
