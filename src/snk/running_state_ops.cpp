#include "running_state_ops.hpp"
#include "rd/vector_util.hpp"
#include <iostream>

namespace snk {

auto apply_queued_directions(snk::running_t state) -> snk::running_t {
  auto last_dir = last_element(state.queued_direction_inputs());
  if (last_dir) {
    state.snake().set_cur_direction(event::to_direction(*last_dir));
  }
  state.queued_direction_inputs().clear();
  return state;
}

auto move_snake(snk::running_t state) -> snk::running_t {
  state.snake().move();
  return state;
}

auto check_collision(snk::running_t state) -> snk::state_t {
  if (snk::is_collided_to_self(state.snake())) {
    return snk::finished_t{ state.score() };
  }
  return state;
}

auto queue_direction(snk::running_t state, event::direction_change dir)
  -> snk::running_t {
  state.queued_direction_inputs().push_back(dir);
  return state;
}

auto to_time_period(std::size_t speed) {
  using namespace std::literals;
  return 1000ms / (speed + 1);
}

auto should_move(snk::running_t const &state,
  std::chrono::time_point<std::chrono::system_clock> cur_time) -> bool {
  auto const movement_time_period = to_time_period(state.speed());
  return cur_time - state.last_tick() >= movement_time_period;
}

}// namespace snk
