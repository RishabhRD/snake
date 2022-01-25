#include "random_fruit_generator.hpp"
#include "random_point.hpp"
#include "board_point_ops.hpp"

namespace snk {
auto random_point = snk::random_point_generator_t{};// NOLINT

auto random_fruit_for(snk::running_t const &state) -> snk::point_t {
  auto pnt = random_point();
  while (true) {
    if (std::none_of(begin(state.snake().body_points()),
          end(state.snake().body_points()),
          [pnt, &state](auto p) {
            return snk::in_board(p, state.board())
                   == snk::in_board(pnt, state.board());
          }))
      break;
    pnt = random_point();
  }
  return pnt;
}
}// namespace snk
