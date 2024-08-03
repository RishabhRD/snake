#include <point.hpp>
#include "test_include.hpp"

const suite point_arithmetic = [] {
  "sum"_test = [] {
    snk::point_t pnt1{ 3, 4 };
    snk::point_t pnt2{ 0, -1 };
    auto new_point = pnt1 + pnt2;
    expect(new_point == snk::point_t{ 3, 3 });
  };
};
