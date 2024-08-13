#pragma once

#include <random>

namespace snk {
class random_gen {
  std::mt19937_64 rng;

 public:
  random_gen(unsigned long seed) : rng(seed) {}

  int operator()(int min, int max) {
    std::uniform_int_distribution<int> gen(min, max);
    return gen(rng);
  }
};
}  // namespace snk
