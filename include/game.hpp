#pragma once

#include <chrono>
#include "board.hpp"
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
  return states::running{.board = board{.width = prop.board_width,
                                        .height = prop.board_height,
                                        .snake = prop.init_snake,
                                        .fruit_pos = prop.init_fruit_pos},
                         .cur_snake_dir = direction::right,
                         .next_snake_dir = direction::right,
                         .time_since_last_move = std::chrono::milliseconds(0),
                         .speed = prop.init_speed};
}
}  // namespace snk
