#pragma once

#include "bounded_point.hpp"
#include "direction.hpp"
#include <vector>
namespace snk {
class snake {
  // Class Invariants:
  //   - body_coords represents body coordinates of snake
  //   - Last element would be snake head
  //   - First element would be snake tail
  //   - Every x coordinate of body_coords have same modulus
  //   - Every y coordinate of body_coords have same modulus
  //   - For every adjacent element of body_coords difference between x coord
  //     is at max 1 and difference between y coord is at max 1
  //   - body_coords.size() >= 1
  std::vector<bounded_point> body_coords;

public:
  snake(bounded_point head_position) : body_coords{ head_position } {}

  void move(direction_t dir) {}
};
}// namespace snk
