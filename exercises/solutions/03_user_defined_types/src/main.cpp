// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"

using WMS::Step;

int main() {
  Step fill{Step::Type::fill, 500};
  Step wash{Step::Type::wash, 1000};
  Step empty{Step::Type::empty, 2000};

  fill.run();
  wash.run();
  empty.run();
}
