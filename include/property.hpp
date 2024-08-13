#pragma once

#include <cstddef>
#include <string_view>
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

struct ui_properties {
  std::size_t scale_factor;
};

struct app_properties {
  snk::game_properties game_properties;
  snk::ui_properties ui_properties;
  std::string_view title;
};
}  // namespace snk
