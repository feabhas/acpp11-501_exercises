// WashStep.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashStep.h"
#include "Motor.h"
#include "Timer.h"

namespace WMS {

static constexpr std::uint32_t on_time{250};
static constexpr std::uint32_t off_time{250};

WashStep::WashStep(Type step_type, std::uint32_t duration,
                   Devices::Motor &motor)
    : Step{step_type, duration}, motor{&motor} {}

void WashStep::run() {
  Step::display();
  auto num_changes = Step::get_duration() / (on_time + off_time);

  for (unsigned int i{0}; i < num_changes; ++i) {
    motor->on();
    sleep(on_time);
    motor->change_direction();
    sleep(off_time);
  }
  motor->off();
}

} // namespace WMS
