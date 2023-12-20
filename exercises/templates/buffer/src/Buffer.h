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
  // Example circular buffer class
  class Buffer {
  public:
    Buffer() = default;

    inline auto add(const unsigned& in_val) -> bool;
    inline auto add(unsigned&& in_val) -> bool;

    inline auto get() -> std::optional<unsigned>;
    inline auto is_empty() const -> bool;
    inline auto size() const -> std::size_t;

  private:
    static constexpr int sz {8};
    using Container = std::array<unsigned, sz>;
    using Iterator  = typename Container::iterator;

    Container buffer{};
    Iterator  read{ std::begin(buffer) };
    Iterator  write{ std::begin(buffer) };
    unsigned  num_items{};
  };

  bool Buffer::add(const unsigned& in_val)
  {
    if (num_items == sz) return false;

    *write = in_val;
    ++num_items;
    ++write;
    if (write == buffer.end()) write = buffer.begin();

    return true;
  }

  bool Buffer::add(unsigned&& in_val)
  {
    if (num_items == sz) return false;

    *write = std::move(in_val);
    ++num_items;
    ++write;
    if (write == buffer.end()) write = buffer.begin();

    return true;
  }

  std::optional<unsigned> Buffer::get()
  {
    if (num_items == 0) return std::nullopt;

    auto selected = read;
    --num_items;
    ++read;
    if (read == buffer.end()) read = buffer.begin();

    return std::move(*selected);
  }

  bool Buffer::is_empty() const
  {
    return (num_items == 0);
  }

  std::size_t Buffer::size() const
  {
    return num_items;
  }
} // namespace Utility

#endif // BUFFER_H_
