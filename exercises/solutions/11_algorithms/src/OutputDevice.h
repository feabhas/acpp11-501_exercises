// OutputDevice.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

namespace Devices {

class OutputDevice {
public:
  virtual ~OutputDevice() = default;

  virtual void display(unsigned value) = 0;
};

}; // namespace Devices

#endif // OUTPUTDEVICE_H_
