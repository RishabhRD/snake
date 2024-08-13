#pragma once

#include <chrono>
#include "board.hpp"
#include "functional.hpp"
#include "game_properties.hpp"
#include "state.hpp"

namespace snk {
// Precondition:
//   - prop.init_speed >= 1
//   - prop.init_fruit_pos.x < prop.board_width
//   - prop.init_fruit_pos.y < prop.board_height
//   - init_snake should be inside board_width and board_height
// Postcondition:
//   - Returns a running state with prop being set
inline snk::states::running init_game(game_properties const& prop) {
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
inline snk::states::state update_state(snk::states::state state,
                                       std::chrono::milliseconds time_passed,
                                       Random& rand) {
  auto time_pass_handler = nostd::overload{
      [](auto cur_state) { return cur_state; },
      [time_passed, &rand](snk::states::running cur_state) {
        return try_move(std::move(cur_state), time_passed, rand);
      },
  };
  return std::visit<snk::states::state>(time_pass_handler, state);
}
}  // namespace snk
