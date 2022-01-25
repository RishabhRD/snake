#include "random_fruit_generator.hpp"
#include "random_point.hpp"
#include "board_point_ops.hpp"

namespace snk {
auto random_point = snk::random_point_generator_t{};// NOLINT

auto random_fruit_for(snk::running_t const &state) -> snk::point_t {
  auto pnt = snk::in_board(random_point(), state.board());
  while (true) {
    if (std::none_of(begin(state.snake().body_points()),
          end(state.snake().body_points()),
          [pnt](auto p) { return p == pnt; }))
      break;
    pnt = snk::in_board(random_point(), state.board());
  }
  return pnt;
}
}// namespace snk
