// Motor.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd
#ifndef MOTOR_H
#define MOTOR_H

#include "GPIO.h"

namespace Devices {
class Motor {
public:
  Motor(GPIO &gpiod);
  ~Motor();

  void on();
  void off();
  void change_direction();

private:
  GPIO &gpio;
};
} // namespace Devices

#endif // MOTOR_H_
