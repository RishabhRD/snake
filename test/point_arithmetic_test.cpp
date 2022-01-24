#include <point.hpp>
#include "test_include.hpp"

suite point_arithmetic = [] {
  "sum"_test = [] {
    snk::point_t p1{ 3, 4 };
    snk::point_t p2{ 0, static_cast<size_t>(-1) };
    auto new_point = p1 + p2;
    expect(new_point == snk::point_t{ 3, 3 });
  };
};
