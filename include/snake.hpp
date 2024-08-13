#pragma once

#include <algorithm>
#include <span>
#include <vector>
#include "direction.hpp"
#include "point.hpp"
#include "point_arithmetic.hpp"

namespace snk {
template <Coordinate CoordType>
class snake {
  // Class Invariants:
  //   - body_coords.size() >= 1
  //   - Every adjacent element (t, h) is st: t comes after h in snake body
  //   - for every adjacent element (x, y) of body_coords:
  //       x == y || is_adjacent(x, y)
  std::vector<point<CoordType>> body_coords;

 public:
  using coord_type = CoordType;

  snake(point<CoordType> head_position) : body_coords{head_position} {}

  // Postcondition:
  //   - Returns snake body (including head) coordinates st for every adjacent
  //     element (t, h) is st: t comes after h in snake body
  std::span<point<CoordType> const> body() const noexcept {
    return body_coords;
  }

  // Postcondition:
  //   - Returns head coordinate of snake
  auto head() const noexcept { return body_coords.back(); }

  // Postcondition:
  //   - adds adjacent_point_towards(head(), dir) as new head;
  void grow(direction dir) {
    body_coords.push_back(adjacent_point_towards(head(), dir));
  }

  // Postcondition:
  //   - for every adjacent points in body (a, b) a becomes b
  //   - head() becomes adjacent_point_towards(head(), dir)
  void move(direction dir) noexcept {
    std::copy(std::next(std::begin(body_coords)), std::end(body_coords),
              std::begin(body_coords));
    body_coords.back() = adjacent_point_towards(head(), dir);
  }

  friend bool operator==(snake const&, snake const&) = default;
};

template <Coordinate CoordType>
snake(point<CoordType>) -> snake<CoordType>;
}  // namespace snk
