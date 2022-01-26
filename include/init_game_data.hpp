#pragma once

#include <cstddef>

namespace snk::game_data {
constexpr static std::size_t num_tiles_x = 20;
constexpr static std::size_t num_tiles_y = 20;
constexpr static std::size_t scaling_factor_x = 30;
constexpr static std::size_t scaling_factor_y = 30;
constexpr static std::size_t win_size_x = scaling_factor_x * num_tiles_x;
constexpr static std::size_t win_size_y = scaling_factor_y * num_tiles_y;
}// namespace snk::game_data
