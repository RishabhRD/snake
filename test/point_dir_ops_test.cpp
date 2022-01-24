#include "test_include.hpp"
#include "point_dir_ops.hpp"

suite point_dir_ops = [] {
  "next point in direction"_test = [] {
    expect(eq(snk::next_point_in_direction({ 3, 4 }, snk::direction_t::east),
      snk::point_t{ 3, 5 }));
  };
};
