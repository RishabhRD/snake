#include "state_ops.hpp"
#include "random_fruit_generator.hpp"
#include "random_point.hpp"
#include "board_point_ops.hpp"
#include <functional>

namespace snk {

auto to_time_period(std::size_t speed) {
  using namespace std::literals;
  return 1000ms / (speed + 1);
}

auto time_passed_from(
  std::chrono::time_point<std::chrono::system_clock> time_point) {
  return std::chrono::system_clock::now() - time_point;
}

void try_moving_snake(snk::running_t &state) {
  auto const movement_time_period = to_time_period(state.speed());
  auto const time_passed = time_passed_from(state.last_tick());
  if (time_passed >= movement_time_period) {
    state.snake().move();
    state.last_tick(std::chrono::system_clock::now());
  }
}

void try_eating_t::operator()(snk::running_t &state,
  auto &&fruit_generator) const {
  if (state.snake().head() == state.fruit_pos()) {
    state.snake().increase_len();
    state.fruit_pos(std::invoke(
      std::forward<decltype(fruit_generator)>(fruit_generator), state));
  }
}

void try_eating_t::operator()(snk::running_t &state) const {
  this->operator()(state, snk::random_fruit_for);
}

void check_collision(snk::state_t &state) {
  auto const &running_state = std::get<snk::running_t>(state);
  if (snk::is_collided_to_self(running_state.snake()))
    state = snk::finished_t{ running_state.score() };
}
}// namespace snk
