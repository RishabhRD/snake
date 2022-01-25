#pragma once
#include <compare>
#include <ostream>

namespace snk {
struct point_t {
  std::size_t x{};// X-AXIS: |
  std::size_t y{};// Y-AXIS: -

  friend auto operator<=>(const point_t &, const point_t &) = default;
  friend std::ostream &operator<<(std::ostream &os, point_t p) {
    os << '(';
    os << p.x << ", " << p.y << ')';
    return os;
  }
};

inline point_t operator+(point_t a, point_t b) {
  return { a.x + b.x, a.y + b.y };
}
}// namespace snk
