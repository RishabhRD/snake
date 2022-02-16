#pragma once

#include "random_fruit_generator.hpp"
#include "state.hpp"
#include <functional>

namespace snk {

auto try_eating(snk::running_t state, auto &&fruit_generator)
  -> snk::running_t {
  if (state.snake().head() == state.fruit_pos()) {
    state.snake().increase_len();
    state.fruit_pos(std::invoke(
      std::forward<decltype(fruit_generator)>(fruit_generator), state));
  }
  return state;
}

inline auto try_eating(snk::running_t state) -> snk::running_t {
  return try_eating(std::move(state), snk::random_fruit_for);
}

auto apply_queued_directions(snk::running_t) -> snk::running_t;

auto move_snake(snk::running_t) -> snk::running_t;

auto check_collision(snk::running_t) -> snk::state_t;

auto queue_direction(snk::running_t, event::direction_change dir)
  -> snk::running_t;

auto should_move(snk::running_t const &,
  std::chrono::time_point<std::chrono::system_clock>) -> bool;
}// namespace snk
