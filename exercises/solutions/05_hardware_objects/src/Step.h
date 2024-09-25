// Step.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd
#ifndef STEP_H
#define STEP_H

#include <cstdint>
#include <string_view>

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
  Step(Type step_type, std::uint32_t step_length);

  Type get_type() const;
  std::uint32_t get_duration() const;
  bool is_valid() const;

  void run();

private:
  void display() const;
  constexpr std::string_view to_string() const;

  Type type{};
  std::uint32_t duration{};
};

} // namespace WMS

#endif // STEP_H_
