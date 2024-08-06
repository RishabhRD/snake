#pragma once

#include "mod_int.hpp"
#include <compare>

namespace snk {
struct bounded_point {
  mod_int x;
  mod_int y;

  // Precondition:
  // a.x.modulus() == b.x.modulus() && a.y.modulus() == b.y.modulus()
  friend constexpr std::strong_ordering operator<=>(const bounded_point &a, const bounded_point &b) = default;
};
}// namespace snk
