#pragma once

#include <functional>
#include "random_fruit_generator.hpp"
#include "state.hpp"

namespace snk {

inline auto try_eating(snk::running_t state) -> snk::state_t {
  if (state.snake().head() == state.fruit_pos()) {
    state.snake().increase_len();
    return fruit_needed_t{std::move(state)};
  }
  return state;
}

auto apply_queued_directions(snk::running_t) -> snk::running_t;

auto move_snake(snk::running_t) -> snk::running_t;

auto check_collision(snk::running_t) -> snk::state_t;

auto queue_direction(snk::running_t,
                     event::direction_change dir) -> snk::running_t;

auto should_move(snk::running_t const&,
                 std::chrono::time_point<std::chrono::system_clock>) -> bool;
}  // namespace snk
