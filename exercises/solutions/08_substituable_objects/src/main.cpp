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

  Step empty{Step::Type::empty, 500};
  Step fill{Step::Type::fill, 1000};
  Step heat{Step::Type::heat, 2000};
  WashStep wash{Step::Type::wash, 2500, motor};
  WashStep rinse{Step::Type::rinse, 2000, motor};
  WashStep spin{Step::Type::spin, 3000, motor};
  WashStep dry{Step::Type::dry, 2400, motor};
  Step complete{Step::Type::complete, 500};

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

  colour_wash.run();
  sleep(2000);
}
