#pragma once

#include <cstddef>
#include "mod_int.hpp"
#include "point.hpp"
#include "snake.hpp"

namespace snk {
struct game_properties {
  std::size_t board_width;
  std::size_t board_height;
  std::size_t init_speed;
  point<std::size_t> init_fruit_pos;
  snk::snake<mod_int> init_snake;
};
}  // namespace snk
