#pragma once

#include "point.hpp"
#include <span>
#include <vector>

namespace snk {
template<Coordinate CoordType> class snake {
  // Class Invariants:
  //   - body_coords.size() >= 1
  //   - Every adjacent element (t, h) is st: t comes after h in snake body
  //   - for every adjacent element (x, y) of body_coords:
  //       x == y || is_adjacent(x, y)
  std::vector<point<CoordType>> body_coords;

public:
  using coord_type = CoordType;

  snake(point<CoordType> head_position) : body_coords{ head_position } {}

  // Postcondition:
  //   - Returns snake body coordinates st for every adjacent element
  //     (t, h) is st: t comes after h in snake body
  std::span<point<CoordType> const> body() const noexcept {
    return body_coords;
  }

  // Postcondition:
  //   - Returns head coordinate of snake
  auto head() const noexcept { return body_coords.back(); }
};

template<Coordinate CoordType> snake(point<CoordType>) -> snake<CoordType>;
}// namespace snk
