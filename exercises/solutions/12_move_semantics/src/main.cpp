// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <cstdint>
#include "Timer.h"
#include "Step.h"
#include "GPIO.h"
#include "SevenSegment.h"
#include "Motor.h"
#include "WashProgramme.h"
#include "WashStep.h"
#include "Console.h"

using Devices::GPIO;

static GPIO make_gpio(STM32F407::AHB1_Device device)
{
    std::cout << "make GPIO" << '\n';
    return GPIO {device};
}

int main()
{
    std::cout << "startup" << '\n';
    GPIO gpio1 = GPIO(STM32F407::AHB1_Device::GPIO_D);
    GPIO gpio2 { std::move(gpio1) };

    gpio1 = std::move(gpio2);

    GPIO gpio4 = make_gpio(STM32F407::AHB1_Device::GPIO_D);
    std::cout << "shutdown" << '\n';
}

// WMS code not used

using WMS::Step;
using WMS::WashStep;

void wms_main()
{
    Devices::GPIO gpiod {STM32F407::AHB1_Device::GPIO_D};
    Devices::SevenSegment display{ gpiod};
    Devices::Motor motor{ gpiod};

    WMS::WashProgramme white_wash {};
    connect(white_wash, display);
    white_wash.add(new Step     {Step::Type::empty,     500});
    white_wash.add(new Step     {Step::Type::fill,     1000});
    white_wash.add(new Step     {Step::Type::heat,     2000});
    white_wash.add(new WashStep {Step::Type::wash,     2500, motor});
    white_wash.add(new WashStep {Step::Type::rinse,    2000, motor});
    white_wash.add(new WashStep {Step::Type::spin,     3000, motor});
    white_wash.add(new WashStep {Step::Type::dry,      2400, motor});
    white_wash.add(new Step     {Step::Type::complete,  500});

    std::cout << "Programm duration: " << white_wash.duration() / 1000 << " secs" << '\n';

    white_wash.run();
    display.blank();

    WMS::WashProgramme colour_wash {white_wash};
    colour_wash.run();
    display.blank();

    WMS::WashProgramme quick_wash {};
    quick_wash = white_wash;
    quick_wash.run();
    display.blank();

    // Devices::Console console {};
    // connect (white_wash, console);
    // white_wash.run();

    sleep(2000);
}
