#pragma once

#include "direction.hpp"
#include "point.hpp"

namespace snk {
template <Coordinate CoordType>
constexpr auto is_adjacent(point<CoordType> p1, point<CoordType> p2) noexcept {
  auto next = [](auto x) {
    return ++x;
  };
  auto prev = [](auto x) {
    return --x;
  };
  auto is_coord_adjacent = [next, prev](auto a, auto b) {
    return next(a) == b || prev(a) == b;
  };
  return (is_coord_adjacent(p1.x, p2.x) && p1.y == p2.y) ||
         (is_coord_adjacent(p1.y, p2.y) && (p1.x == p2.x));
}

// Postcondition:
//   - returns adjecent point to p in direction dir
template <Coordinate CoordType>
constexpr auto adjacent_point_towards(point<CoordType> p,
                                      direction dir) noexcept {
  if (dir == direction::right)
    ++p.x;
  else if (dir == direction::left)
    --p.x;

  if (dir == direction::down)
    ++p.y;
  else if (dir == direction::up)
    --p.y;

  return p;
}
}  // namespace snk
