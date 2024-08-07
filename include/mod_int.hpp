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

  constexpr int value() const noexcept { return val; }
  constexpr int modulus() const noexcept { return mod; }

  // Precondition: a.mod == b.mod
  // Postcondition: result.modulus() == a.modulus()
  constexpr friend std::strong_ordering operator<=>(mod_int,
    mod_int) noexcept = default;

  // Precondition: a.mod == b.mod
  // Postcondition: result.modulus() == a.modulus()
  constexpr friend mod_int operator+(mod_int a, mod_int b) noexcept {
    return { (a.val + b.val) % a.mod, a.mod };
  }

  // Precondition: a.mod == b.mod
  // Postcondition: result.modulus() == a.modulus()
  constexpr friend mod_int operator-(mod_int a, mod_int b) noexcept {
    return { (a.val - b.val + a.mod) % a.mod, a.mod };
  }

  // Postcondition: &result == &a
  constexpr friend mod_int &operator++(mod_int &a) noexcept {
    a.val = (a.val + 1) % a.mod;
    return a;
  }

  // Postcondition: result.modulus() == a.modulus()
  constexpr friend mod_int operator++(mod_int &a, int) noexcept {
    mod_int old = a;
    ++a;
    return old;
  }

  // Postcondition: &result == &a
  constexpr friend mod_int &operator--(mod_int &a) noexcept {
    a.val = (a.val - 1 + a.mod) % a.mod;
    return a;
  }

  // Postcondition: result.modulus() == a.modulus()
  constexpr friend mod_int operator--(mod_int &a, int) noexcept {
    mod_int old = a;
    --a;
    return old;
  }
};
}// namespace snk
