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

#include "Buffer.h"
#include <cassert>

#include <string>
using Utility::Buffer;

constexpr std::size_t sz = 16;

int main() {
  Buffer<std::string, sz> buffer{};

  {
    puts("Testing empty state");
    assert(buffer.size() == 0);
    assert(buffer.is_empty() == true);
    assert(buffer.get() == std::nullopt);
  }
  {
    puts("Testing add/remove one element");
    assert(buffer.add("Hello"));
    assert(buffer.size() == 1);
    assert(!buffer.is_empty());
    auto data = buffer.get();
    assert(data.has_value());
    assert(*data == std::string("Hello"));
    assert(buffer.size() == 0);
    assert(buffer.is_empty());
  }
  {
    puts("Testing fill to full element, read to empty");
    for (unsigned i = 0; i < sz; ++i) {
      assert(buffer.add("Hello_" + std::to_string(i)));
      assert(buffer.size() == i + 1);
    }
    assert(buffer.size() == sz);
    assert(!buffer.add("overflow"));
    assert(buffer.size() == sz);
    for (unsigned i = 0; i < sz; ++i) {
      auto data = buffer.get();
      assert(data.has_value());
      assert(*data == std::string("Hello_" + std::to_string(i)));
    }
    assert(buffer.get() == std::nullopt);
  }

  {
    puts("Testing wrap around");
    for (unsigned i = 0; i < sz; ++i) {
      auto rv = buffer.add("Hello_" + std::to_string(i));
      assert(rv == true);
      assert(buffer.size() == i + 1);
    }
    for (unsigned i = 0; i < sz / 2; ++i) {
      auto data = buffer.get();
      assert(data.has_value());
      assert(*data == std::string("Hello_" + std::to_string(i)));
    }
    auto rv = buffer.add("wrap around");
    assert(rv == true);
    for (unsigned i = sz / 2; i < sz; ++i) {
      auto data = buffer.get();
      assert(data.has_value());
      assert(*data == std::string("Hello_" + std::to_string(i)));
    }
    auto data = buffer.get();
    assert(data.has_value());
    assert(*data == std::string("wrap around"));
    assert(buffer.is_empty());
  }
}
