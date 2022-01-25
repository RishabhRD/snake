#include "state_ops.hpp"
#include "random_point.hpp"
#include "board_point_ops.hpp"
#include <algorithm>

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

void try_eating(snk::running_t &state) {
  if (state.snake().head() == state.fruit_pos()) {
    state.snake().increase_len();
    // TODO: randomness should be dependency injection, for testing purposes
    state.fruit_pos(random_fruit_for(state));
  }
}

void check_collision(snk::state_t &state) {
  auto const &running_state = std::get<snk::running_t>(state);
  if (snk::is_collided_to_self(running_state.snake()))
    state = snk::finished_t{ running_state.score() };
}
}// namespace snk
