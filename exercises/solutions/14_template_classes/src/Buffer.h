// Buffer.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include <array>
#include <cstddef>
#include <optional>

namespace Utility
{
  template<typename T = int, std::size_t sz = 8>
  class Buffer {
  public:
    using value_type = T;
    Buffer() = default;

    auto add(const value_type& in_val) -> bool;
    auto add(value_type&& in_val) -> bool;

    auto get() -> std::optional<value_type>;
    auto is_empty() const -> bool;
    auto size() const -> std::size_t;

  private:
    using Container = std::array<value_type, sz>;
    using Iterator  = typename Container::iterator;

    Container buffer{};
    Iterator  read{ std::begin(buffer) };
    Iterator  write{ std::begin(buffer) };
    unsigned  num_items{};
  };

  template<typename T, std::size_t sz>
  bool Buffer<T, sz>::add(const value_type& in_val)
  {
    if (num_items == sz) return false;

    *write = in_val;
    ++num_items;
    ++write;
    if (write == buffer.end()) write = buffer.begin();

    return true;
  }

  template<typename T, std::size_t sz>
  bool Buffer<T,sz>::add(value_type&& in_val)
  {
    if (num_items == sz) return false;

    *write = std::move(in_val);
    ++num_items;
    ++write;
    if (write == buffer.end()) write = buffer.begin();

    return true;
  }

  template<typename T, std::size_t sz>
  std::optional<typename Buffer<T, sz>::value_type> Buffer<T, sz>::get()
  {
    if (num_items == 0) return std::nullopt;

    auto selected = read;
    --num_items;
    ++read;
    if (read == buffer.end()) read = buffer.begin();

    return std::move(*selected);
  }

  template<typename T, std::size_t sz>
  bool Buffer<T, sz>::is_empty() const
  {
    return (num_items == 0);
  }

  template<typename T, std::size_t sz>
  std::size_t Buffer<T, sz>::size() const
  {
    return num_items;
  }
} // namespace Utility
#endif // BUFFER_H_
