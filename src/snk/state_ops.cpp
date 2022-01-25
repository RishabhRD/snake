#include "state_ops.hpp"
#include "board_point_ops.hpp"
#include <functional>

namespace snk {
void check_collision(snk::state_t &state) {
  auto const &running_state = std::get<snk::running_t>(state);
  if (snk::is_collided_to_self(running_state.snake())) {
    state = snk::finished_t{ running_state.score() };
  }
}
}// namespace snk
