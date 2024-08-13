#pragma once

#include <chrono>
#include "board.hpp"
#include "board_arithmetic.hpp"
#include "direction.hpp"
#include "functional.hpp"
#include "property.hpp"
#include "state.hpp"

namespace snk {
// Precondition:
//   - state.time_since_last_move < state.move_threshold
//   - time_passed <= state.move_threshold
// Postcondition:
//   - Returns true if total time elapsed is >= move_threshold
//   - sets the total time elapsed as time since last move. If that is greater
//     than move threshold then reduce move threshold from same
inline bool apply_time_passed(states::running& state,
                              std::chrono::milliseconds time_passed) {
  state.time_since_last_move += time_passed;
  if (state.time_since_last_move > state.move_threshold) {
    state.time_since_last_move -= state.move_threshold;
    return true;
  }
  return false;
}

// Postcondition:
//   - if snake doesn't eat food, return false
//   - if it eats, and this leads to winning position returns true
//   - otherwise, update state with new fruit position and retrns false
template <typename Random>
bool try_eat_fruit(snk::states::running& state, Random&& rand) {
  if (ate_fruit(state.board)) {
    auto new_fruit_pos = generate_fruit(state.board, rand);
    if (!new_fruit_pos.has_value())
      return true;
    state.board.fruit_pos = *new_fruit_pos;
    state.board.snake.grow(state.cur_snake_dir);
  }
  return false;
}

// Postcondition:
//   - return states::lost{state} if there is a collision on board
//   - otherwise returns state
inline states::state with_potential_collision(snk::states::running state) {
  if (has_collision(state.board)) {
    return states::lost{std::move(state)};
  }
  return state;
}

// Postcondition:
//   - Moves the snake in current direction
//   - Then try to eat fruit
//   - If it leads to winning then return winning state
//   - Otherwise try potential collision
template <typename Random>
states::state move(snk::states::running state, Random&& rand) {
  state.board.snake.move(state.cur_snake_dir);
  auto is_winning = try_eat_fruit(state, rand);
  if (is_winning)
    return states::win{std::move(state)};
  return with_potential_collision(std::move(state));
}

// Postcondition:
//   - If next direction is opposite of current direction, then next direction
//     is current direction
//   - Make current direction to next direction
inline auto apply_direction(snk::states::running state) {
  if (state.next_snake_dir == opposite(state.cur_snake_dir))
    state.next_snake_dir = state.cur_snake_dir;
  state.cur_snake_dir = state.next_snake_dir;
  return state;
}

// Postcondition:
//   - Apply time passed effect on state
//   - Then apply direction
//   - If time passed effect suggests to move then move otherwise return same
//     state
template <typename Random>
snk::states::state try_move(snk::states::running state,
                            std::chrono::milliseconds time_passed,
                            Random&& rand) {
  auto to_move = apply_time_passed(state, time_passed);
  state = apply_direction(std::move(state));
  if (to_move)
    return move(std::move(state), rand);
  else
    return state;
}

// Precondition:
//   - prop.init_speed >= 1
//   - prop.init_fruit_pos.x < prop.board_width
//   - prop.init_fruit_pos.y < prop.board_height
//   - init_snake should be inside board_width and board_height
// Postcondition:
//   - Returns a running state with prop being set
inline states::running init_game(game_properties const& prop) {
  auto move_threshold = std::chrono::milliseconds{1000 / prop.init_speed};
  return states::running{.board = board{.width = prop.board_width,
                                        .height = prop.board_height,
                                        .snake = prop.init_snake,
                                        .fruit_pos = prop.init_fruit_pos},
                         .cur_snake_dir = direction::right,
                         .next_snake_dir = direction::right,
                         .time_since_last_move = std::chrono::milliseconds(0),
                         .move_threshold = move_threshold};
}

// Precondition:
//   - time_passed <= state.move_threshold (if state is running)
// Postcondition:
//   - If state is running then try_move(state, time_passed, rand)
//   - Otherwise just return the same
template <typename Random>
inline states::state after_time(std::chrono::milliseconds time_passed,
                                states::state state, Random& rand) {
  auto time_pass_handler = nostd::overload{
      [](auto cur_state) { return cur_state; },
      [time_passed, &rand](snk::states::running cur_state) {
        return try_move(std::move(cur_state), time_passed, rand);
      },
  };
  return std::visit<snk::states::state>(time_pass_handler, state);
}
}  // namespace snk
