#pragma once

#include "point.hpp"
#include "direction.hpp"

namespace snk{
  point_t to_point(direction_t dir);

  point_t next_point_in_direction(point_t cur_point, direction_t cur_dir);
}
