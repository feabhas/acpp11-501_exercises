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

#include <cassert>
#include "Buffer.h"

using Utility::Buffer;

constexpr std::size_t sz = 16;

int main()
{
  Buffer<unsigned, sz> buffer{};

  {
    puts("Testing empty state");
    assert(buffer.size() == 0);
    assert(buffer.is_empty() == true);
    assert(buffer.get() == std::nullopt);
  }
  {
    puts("Testing add/remove one element");
    assert(buffer.add(42u));
    assert(buffer.size() == 1);
    assert(!buffer.is_empty());
    auto data = buffer.get();
    assert(data.has_value());
    assert(*data == 42u);
    assert(buffer.size() == 0);
    assert(buffer.is_empty());
  }
  {
    puts("Testing fill to full element, read to empty");
    for (unsigned i = 0; i < sz; ++i) {
      assert(buffer.add(i));
      assert(buffer.size() == i + 1);
    }
    assert(buffer.size() == sz);
    assert(!buffer.add(101u));
    assert(buffer.size() == sz);
    for (unsigned i = 0; i < sz; ++i) {
      auto data = buffer.get();
      assert(data.has_value());
      assert(*data == i);
    }
    assert(buffer.get() == std::nullopt);
  }

  {
    puts("Testing wrap around");
    for (unsigned i = 0; i < sz; ++i) {
      auto rv = buffer.add(i);
      assert(rv == true);
      assert(buffer.size() == i + 1);
    }
    for (unsigned i = 0; i < sz / 2; ++i) {
      auto data = buffer.get();
      assert(data.has_value());
      assert(*data == i);
    }
    auto rv = buffer.add(102u);
    assert(rv == true);
    for (unsigned i = sz / 2; i < sz; ++i) {
      auto data = buffer.get();
      assert(data.has_value());
      assert(*data == i);
    }
    auto data = buffer.get();
    assert(data.has_value());
    assert(*data == 102);
    assert(buffer.is_empty());
  }
}

// unused WMS code

using WMS::Step;
using WMS::WashStep;

void wms_main()
{
    Devices::GPIO gpiod {STM32F407::AHB1_Device::GPIO_D};
    Devices::SevenSegment display{ gpiod};
    Devices::Motor motor{ gpiod};

    WMS::WashProgramme white_wash {};
    connect(white_wash, display);
    white_wash.add(std::make_unique<Step>     (Step::Type::empty,     500));
    white_wash.add(std::make_unique<Step>     (Step::Type::fill,     1000));
    white_wash.add(std::make_unique<Step>     (Step::Type::heat,     2000));
    white_wash.add(std::make_unique<WashStep> (Step::Type::wash,     2500, motor));
    white_wash.add(std::make_unique<WashStep> (Step::Type::rinse,    2000, motor));
    white_wash.add(std::make_unique<WashStep> (Step::Type::spin,     3000, motor));
    white_wash.add(std::make_unique<WashStep> (Step::Type::dry,      2400, motor));
    white_wash.add(std::make_unique<Step>     (Step::Type::complete,  500));

    std::cout << "Programm duration: " << white_wash.duration() / 1000 << " secs" << '\n';

    white_wash.run();

    display.blank();
    sleep(2000);
}
