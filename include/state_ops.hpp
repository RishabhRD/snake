#pragma once

#include "board_point_ops.hpp"
#include "random_fruit_generator.hpp"
#include "state.hpp"
#include <cstddef>
#include <chrono>
#include <functional>
namespace snk {

inline auto to_time_period(std::size_t speed) {
  using namespace std::literals;
  return 1000ms / (speed + 1);
}

struct try_moving_snake_t {
  auto operator()(snk::running_t &state, auto &&now) const -> void {
    auto const cur_time = std::invoke(std::forward<decltype(now)>(now));
    auto const movement_time_period = to_time_period(state.speed());
    auto const time_passed = cur_time - state.last_tick();
    if (time_passed >= movement_time_period) {
      state.snake().move();
      state.last_tick(cur_time);
    }
  }

  auto operator()(snk::running_t &state) const {
    this->operator()(state, std::chrono::system_clock::now);
  }
};
inline try_moving_snake_t const try_moving_snake{};

struct try_eating_t {
  void operator()(snk::running_t &state, auto &&fruit_generator) const {
    if (snk::in_board(state.snake().head(), state.board())
        == snk::in_board(state.fruit_pos(), state.board())) {
      state.snake().increase_len();
      state.fruit_pos(std::invoke(
        std::forward<decltype(fruit_generator)>(fruit_generator), state));
    }
  }
  void operator()(snk::running_t &state) const {
    this->operator()(state, snk::random_fruit_for);
  }
};
inline auto const try_eating = try_eating_t{};

void check_collision(snk::state_t &state);
}// namespace snk
