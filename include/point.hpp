#pragma once

#include "mod_int.hpp"
#include <compare>

namespace snk {
struct point_t {
  mod_int x;
  mod_int y;

  // Precondition:
  // a.x.modulus() == b.x.modulus() && a.y.modulus() == b.y.modulus()
  friend constexpr std::strong_ordering operator<=>(const point_t &a, const point_t &b) = default;
};
}// namespace snk
