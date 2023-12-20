// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <cassert>
#include "Buffer.h"

using Utility::Buffer;

int main()
{
  Buffer buffer{};

  {
    puts("Minimal testing");
    assert(buffer.is_empty() == true);
    assert(buffer.add(42u));
    assert(buffer.size() == 1);
    auto data = buffer.get();
    assert(*data == 42u);
    assert(buffer.is_empty());
  }
}
