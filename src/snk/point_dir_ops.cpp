#include "point_dir_ops.hpp"

namespace snk {
auto to_point(direction_t dir) -> point_t {
  switch (dir) {
  case direction_t::south:
    return { 1, 0 };
  case direction_t::north:
    return { static_cast<std::size_t>(-1), 0 };
  case direction_t::east:
    return { 0, 1 };
  case direction_t::west:
    return { 0, static_cast<std::size_t>(-1) };
  }
  throw "Unreachable";
}

point_t next_point_in_direction(point_t cur_point, direction_t cur_dir) {
  return cur_point + to_point(cur_dir);
}
}// namespace snk
