// Step.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#ifndef STEP_H
#define STEP_H

#include <cstdint>

namespace WMS {

class Step {
public:
  enum class Type {
    invalid,
    empty,
    fill,
    heat,
    wash,
    rinse,
    spin,
    dry,
    complete
  };
  Step() = default;
  Step(Type step_type, uint32_t step_length);

  Type get_type() const;
  uint32_t get_duration() const;
  bool is_valid() const;
  void run();
  const char *to_string() const;
  void display() const;

private:
  Type type{Type::invalid};
  uint32_t duration{0};
};

} // namespace WMS

#endif // STEP_H
