#include "board_point_ops.hpp"

namespace snk {
auto in_board(snk::point_t point, snk::board_t board) -> snk::point_t {
  return snk::point_t{ point.x % board.height(), point.y % board.width() };
}
}// namespace snk
