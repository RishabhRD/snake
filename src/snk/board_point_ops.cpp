#include "board_point_ops.hpp"

namespace snk {
auto modulo(int num, int div) -> int { return ((num % div) + div) % div; }

auto in_board(snk::point_t point, snk::board_t board) -> snk::point_t {
  return snk::point_t{ modulo(point.x, board.width()),
    modulo(point.y, board.width()) };
}
}// namespace snk
