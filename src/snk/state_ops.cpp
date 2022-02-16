#include "state_ops.hpp"
#include "board_point_ops.hpp"
#include "init_game_data.hpp"
#include "input_handler.hpp"
#include "rd/variant_then.hpp"
#include <functional>

namespace snk {

auto apply_direction(snk::event::direction_change dir, snk::running_t &state) {
  state.snake().set_cur_direction(to_direction(dir));
}

auto is_direction_input(snk::event::direction_change const input) -> bool {
  return input == snk::event::direction_change::down
         or input == snk::event::direction_change::up
         or input == snk::event::direction_change::right
         or input == snk::event::direction_change::left;
}

auto get_last_direction_input(auto const &rng)
  -> std::optional<snk::event::direction_change> {
  auto dir_input_itr = std::find_if(std::rbegin(rng),
    std::rend(rng),
    [](auto input) { return is_direction_input(input); });
  if (dir_input_itr == std::rend(rng)) return std::nullopt;
  return *dir_input_itr;
}

auto check_collision(snk::state_t &state) -> void {
  auto const &running_state = std::get<snk::running_t>(state);
  if (snk::is_collided_to_self(running_state.snake())) {
    state = snk::finished_t{ running_state.score() };
  }
}

auto move_snake(snk::running_t &state) -> void { state.snake().move(); }

auto process_queued_directions(snk::state_t &game_state) -> void {
  if (rd::is<snk::running_t>(game_state)) {
    auto const inputs =
      std::get<snk::running_t>(game_state).queued_direction_inputs();
    auto const opt_dir_input = get_last_direction_input(inputs);
    if (opt_dir_input and rd::is<snk::running_t>(game_state))
      apply_direction(*opt_dir_input, std::get<snk::running_t>(game_state));
  }
}

auto enqueue_direction_input(snk::running_t &state,
  snk::event::direction_change input) -> void {
  state.queued_direction_inputs().push_back(input);
}

auto quit_game(snk::state_t &state) -> void { state = snk::closed_t{}; }

auto conditional_play_pause(snk::state_t &state) -> void {
  if (rd::is<snk::running_t>(state)) {
    state = snk::paused_t{ std::get<snk::running_t>(state) };
  } else if (rd::is<snk::paused_t>(state)) {
    state = std::get<snk::paused_t>(state).running_state();
  }
}

auto start_game(snk::state_t &state) -> void {
  constexpr static std::size_t speed = 6;
  constexpr static snk::point_t init_fruit_position = { 17, 10 };

  if (!rd::is<snk::closed_t>(state)) {
    snk::board_t board{ snk::game_data::num_tiles_x,
      snk::game_data::num_tiles_y };
    snk::snake_t init_snake{
      { { 9, 10 }, { 10, 10 }, { 11, 10 } }, snk::direction_t::east, board
    };
    state = snk::running_t{ std::move(init_snake),
      init_fruit_position,
      speed,
      std::chrono::system_clock::now() };
  }
}
}// namespace snk
