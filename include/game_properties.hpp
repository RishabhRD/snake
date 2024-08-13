#pragma once

#include <cstddef>
#include "point.hpp"

namespace snk {
struct game_properties {
  std::size_t board_width;
  std::size_t board_height;
  std::size_t init_speed;
  point<std::size_t> init_fruit_pos;
  point<std::size_t> init_snake_head_pos;
};
}  // namespace snk
