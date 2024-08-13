#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string>
#include "property.hpp"

namespace snk {
inline app_properties init_config(int argc, char** argv) {
  snk::snake snake{point<mod_int>{{2, 30}, {15, 30}}};
  snk::game_properties game_properties{
      .board_width = 30,
      .board_height = 30,
      .init_speed = 3,
      .init_fruit_pos = {15, 15},
      .init_snake = std::move(snake),
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
      .ui_properties = {10},
      .title = "Snake",
  };
}
}  // namespace snk
