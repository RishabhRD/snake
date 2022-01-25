#pragma once

#include "point.hpp"
#include <cstddef>
#include <random>

namespace snk {

class random_point_generator_t {
  std::random_device rd;
  std::mt19937 mt;
  std::uniform_int_distribution<int> dist;

public:
  random_point_generator_t() : mt(rd()) {}

  auto operator()() { return snk::point_t{ dist(mt), dist(mt) }; }
};

}// namespace snk
