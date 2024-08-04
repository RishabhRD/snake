#pragma once

#include "math.hpp"
#include <compare>

namespace snk {
class mod_int {
  int val;
  int mod;

public:
  constexpr mod_int(int a_val, int a_mod)
    : val(nostd::mod(a_val, a_mod)), mod(a_mod) {}

  constexpr int value() const { return val; }
  constexpr int modulus() const { return mod; }

  // Precondition: a.mod == b.mod
  constexpr friend std::strong_ordering operator<=>(mod_int, mod_int) = default;

  // Precondition: a.mod == b.mod
  constexpr friend mod_int operator+(mod_int a, mod_int b) {
    return { (a.val + b.val) % a.mod, a.mod };
  }

  // Precondition: a.mod == b.mod
  constexpr friend mod_int operator-(mod_int a, mod_int b) {
    return { (a.val - b.val + a.mod) % a.mod, a.mod };
  }
};
}// namespace snk
