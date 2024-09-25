// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Motor.h"
#include "SevenSegment.h"
#include "Timer.h"
#include "WashProgramme.h"
#include <cstdint>
#include <iostream>

[[maybe_unused]] static void test_seven_segment(Devices::GPIO &gpio);
[[maybe_unused]] static void test_motor(Devices::GPIO &gpio);

using WMS::Step;

int main() {
  Devices::GPIO gpiod{STM32F407::AHB1_Device::GPIO_D};

#if 0
  test_seven_segment(gpiod);
  test_motor(gpiod);
#else

  Devices::SevenSegment display{gpiod};
  WMS::WashProgramme colour_wash{};

  colour_wash.add(Step::Type::fill, 1000);
  colour_wash.add(Step::Type::heat, 2000);
  colour_wash.add(Step::Type::wash, 2500);
  colour_wash.add(Step::Type::empty, 500);
  colour_wash.add(Step::Type::fill, 1000);
  colour_wash.add(Step::Type::rinse, 2000);
  colour_wash.add(Step::Type::empty, 500);
  colour_wash.add(Step::Type::spin, 3000);
  colour_wash.add(Step::Type::dry, 2400);
  colour_wash.add(Step::Type::complete, 500);

  connect(colour_wash, display);
  colour_wash.run();
  display.blank();
#endif
}

void test_seven_segment(Devices::GPIO &gpio) {
  Devices::SevenSegment sseg{gpio};
  for (unsigned i = 0; i < 10; ++i) {
    sseg.display(i);
    sleep(1000);
  }
  sseg.blank();
}

void test_motor(Devices::GPIO &gpio) {
  Devices::Motor motor{gpio};
  for (unsigned i = 0; i < 5; ++i) {
    motor.on();
    sleep(1000);
    motor.off();
    sleep(500);
    motor.change_direction();
  }
}
