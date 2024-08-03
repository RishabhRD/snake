#include "point_dir_ops.hpp"

namespace snk {
auto to_point(direction_t dir) -> point_t {
  switch (dir) {
  case direction_t::down:
    return { 0, 1 };
  case direction_t::up:
    return { 0, -1 };
  case direction_t::right:
    return { 1, 0 };
  case direction_t::left:
    return { -1, 0 };
  }
  return { 0, 0 };// unreachable
}

point_t next_point_in_direction(point_t cur_point, direction_t cur_dir) {
  return cur_point + to_point(cur_dir);
}
}// namespace snk
