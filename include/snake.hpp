#pragma once

#include "point.hpp"
#include <vector>
namespace snk {
template<Coordinate CoordType> class snake {
  // Class Invariants:
  //   - body_coords.size() >= 1
  //   - body_coords represents body coordinates of snake with last element
  //     being head and first element being tail
  //   - for every adjacent element (x, y) of body_coords:
  //       x == y || is_adjacent(x, y)
  std::vector<point<CoordType>> body_coords;

public:
  using coord_type = CoordType;

  snake(point<CoordType> head_position) : body_coords{ head_position } {}
};

template<Coordinate CoordType> snake(point<CoordType>) -> snake<CoordType>;
}// namespace snk
