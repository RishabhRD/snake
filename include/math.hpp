#pragma once

namespace nostd {
constexpr int mod(int n, int modulus) {
  return ((n % modulus) + modulus) % modulus;
}
}  // namespace nostd
