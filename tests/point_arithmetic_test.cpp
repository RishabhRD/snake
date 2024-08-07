#include "point_arithmetic.hpp"
#include "doctest.hpp"
#include "point.hpp"

using namespace snk;

test("adjacent_point_towards") {
  req(adjacent_point_towards(point{1, 1}, direction::right) == point{2, 1});
  req(adjacent_point_towards(point{1, 1}, direction::left) == point{0, 1});
  req(adjacent_point_towards(point{1, 1}, direction::up) == point{1, 0});
  req(adjacent_point_towards(point{1, 1}, direction::down) == point{1, 2});
}

test("is_adjacent") {
  req(is_adjacent(point{1, 1}, point{0, 1}));
  req(is_adjacent(point{1, 1}, point{1, 0}));
  req(is_adjacent(point{1, 1}, point{2, 1}));
  req(is_adjacent(point{1, 1}, point{1, 2}));
  req_false(is_adjacent(point{1, 1}, point{1, 1}));
  req_false(is_adjacent(point{1, 1}, point{1, 3}));
  req_false(is_adjacent(point{1, 1}, point{-1, 3}));
}
