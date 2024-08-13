#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string>
#include "property.hpp"
#include "ui/color.hpp"

namespace snk {
inline app_properties init_config(int argc, char** argv) {
  auto const width = 20;
  auto const height = 20;
  snk::snake snake{point<mod_int>{{2, width}, {height / 2, height}}};
  snake.grow(direction::right);
  snake.grow(direction::right);
  snk::game_properties game_properties{
      .board_width = width,
      .board_height = height,
      .init_speed = 8,
      .init_fruit_pos = {width / 2, height / 2},
      .init_snake = std::move(snake),
  };

  snk::ui_properties ui_properties{
      .scale_factor = 30,
      .bg_color = ui::color{0, 0, 0},
      .head_color = ui::color{0, 0, 255},
      .body_color = ui::color{0, 255, 0},
      .fruit_color = ui::color{255, 0, 0},
  };
  if (argc >= 2) {
    try {
      auto new_speed = std::stoi(argv[1]);
      if (new_speed <= 0) {
        throw std::runtime_error{std::string{"bad speed value: "} + '0'};
      }
      game_properties.init_speed = static_cast<std::size_t>(new_speed);
    } catch (...) {
      throw std::runtime_error{std::string{"bad speed value: "} +
                               std::string{argv[1]}};
    }
  }
  return app_properties{
      .game_properties = std::move(game_properties),
      .ui_properties = ui_properties,
      .title = "Snake",
  };
}
}  // namespace snk
