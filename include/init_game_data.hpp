#pragma once

namespace snk::game_data {
constexpr static int num_tiles_x = 20;
constexpr static int num_tiles_y = 20;
constexpr static int scaling_factor_x = 30;
constexpr static int scaling_factor_y = 30;
constexpr static int win_size_x = scaling_factor_x * num_tiles_x;
constexpr static int win_size_y = scaling_factor_y * num_tiles_y;
}  // namespace snk::game_data
