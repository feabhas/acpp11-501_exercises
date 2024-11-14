// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Motor.h"
#include "SevenSegment.h"
#include "Step.h"
#include "Timer.h"
#include "WashProgramme.h"
#include "WashStep.h"
#include <cstdint>
#include <iostream>

using WMS::Step;
using WMS::WashStep;

int main() {
  Devices::GPIO gpiod{STM32F407::AHB1_Device::GPIO_D};
  Devices::SevenSegment display{gpiod};
  Devices::Motor motor{gpiod};

  auto fill = std::make_shared<Step>(Step::Type::fill, 1000);
  auto heat = std::make_shared<Step>(Step::Type::heat, 2000);
  auto wash = std::make_shared<WashStep>(Step::Type::wash, 2500, motor);
  auto empty = std::make_shared<Step>(Step::Type::empty, 500);
  auto rinse = std::make_shared<WashStep>(Step::Type::rinse, 2000, motor);
  auto spin = std::make_shared<WashStep>(Step::Type::spin, 3000, motor);
  auto dry = std::make_shared<WashStep>(Step::Type::dry, 2400, motor);
  auto complete = std::make_shared<Step>(Step::Type::complete, 500);

  WMS::WashProgramme colour_wash{};
  connect(colour_wash, display);

  colour_wash.add(fill);
  colour_wash.add(heat);
  colour_wash.add(wash);
  colour_wash.add(empty);
  colour_wash.add(fill);
  colour_wash.add(rinse);
  colour_wash.add(empty);
  colour_wash.add(spin);
  colour_wash.add(dry);
  colour_wash.add(complete);

  std::cout << "Programm duration: " << colour_wash.duration() / 1000 << "s\n";

  // colour_wash.run();

  WMS::WashProgramme white_wash{fill, wash,  empty, fill, heat, wash,    empty,
                                fill, rinse, empty, spin, dry,  complete};
  connect(white_wash, display);
  std::cout << "White wash duration : " << white_wash.duration() / 1000.0
            << "s\n";
  white_wash.run();

  sleep(2000);
}
