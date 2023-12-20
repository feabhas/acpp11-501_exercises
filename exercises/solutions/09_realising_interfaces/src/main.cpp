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

using WMS::Step;
using WMS::WashStep;

int main()
{
    Devices::GPIO gpiod {STM32F407::AHB1_Device::GPIO_D};
    Devices::SevenSegment display{ gpiod};
    Devices::Motor motor{ gpiod};

    Step empty     {Step::Type::empty,     500};
    Step fill      {Step::Type::fill,     1000};
    Step heat      {Step::Type::heat,     2000};
    WashStep wash  {Step::Type::wash,     2500, motor};
    WashStep rinse {Step::Type::rinse,    2000, motor};
    WashStep spin  {Step::Type::spin,     3000, motor};
    WashStep dry   {Step::Type::dry,      2400, motor};
    Step complete  {Step::Type::complete,  500};

    WMS::WashProgramme white_wash {};
    white_wash.add(&empty);
    white_wash.add(&fill);
    white_wash.add(&heat);
    white_wash.add(&wash);
    white_wash.add(&rinse);
    white_wash.add(&spin);
    white_wash.add(&dry);
    white_wash.add(&complete);

    connect(white_wash, display);
    white_wash.run();
    display.blank();

    Devices::Console console {};
    connect (white_wash, console);
    white_wash.run();

    sleep(2000);
}
