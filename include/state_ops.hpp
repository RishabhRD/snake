#pragma once

#include "board_point_ops.hpp"
#include "random_fruit_generator.hpp"
#include "state.hpp"
#include "rd/variant_then.hpp"
#include <cstddef>
#include <chrono>
#include <functional>
namespace snk {

inline auto to_time_period(std::size_t speed) {
  using namespace std::literals;
  return 1000ms / (speed + 1);
}

struct try_eating_t {
  void operator()(snk::running_t &state, auto &&fruit_generator) const {
    if (state.snake().head() == state.fruit_pos()) {
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

void after_time_period(snk::state_t &state, auto &&func, auto &&now) {
  if (rd::is<snk::running_t>(state)) {
    auto const cur_time = std::invoke(std::forward<decltype(now)>(now));
    auto const movement_time_period =
      to_time_period(std::get<snk::running_t>(state).speed());
    auto const time_passed =
      cur_time - std::get<snk::running_t>(state).last_tick();
    if (time_passed >= movement_time_period) {
      std::get<snk::running_t>(state).last_tick(cur_time);
      std::invoke(std::forward<decltype(func)>(func), state);
    }
  }
}

void after_time_period(snk::state_t &state, auto &&func) {
  after_time_period(
    state, std::forward<decltype(func)>(func), std::chrono::system_clock::now);
}

void check_collision(snk::state_t &state);
void move_snake(snk::running_t &state);
void process_queued_directions(snk::state_t &state);
auto enqueue_direction_input(snk::running_t &state,
  snk::direction_input_t input) -> void;
auto quit_game(snk::state_t &state) -> void;
auto conditional_play_pause(snk::state_t &state) -> void;
}// namespace snk
