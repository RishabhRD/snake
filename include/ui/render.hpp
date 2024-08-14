#pragma once

#include <iostream>
#include <variant>
#include "board_arithmetic.hpp"
#include "property.hpp"
#include "state.hpp"
#include "ui/color.hpp"
#include "ui/window.hpp"

namespace snk {
template <ui::Window window>
void draw_square(std::size_t x, std::size_t y, std::size_t scaling_factor,
                 ui::color color, window& win) {
  win.draw_square(x * scaling_factor, y * scaling_factor, scaling_factor,
                  color);
}

struct ui_renderer {
  ui_properties ui_prop;

  template <ui::Window window>
  void operator()(states::init, window& win) const {
    if (!win.draw_image("data/title.png")) {
      std::cerr << "Can't load backgound\n";
    }
  }

  template <ui::Window window>
  void operator()(states::running const& state, window& win) const {
    auto matrix = create_board_matrix(state.board);
    win.clear(ui_prop.bg_color);
    for (std::size_t i{}; i < matrix.size(); ++i) {
      for (std::size_t j{}; j < matrix[0].size(); ++j) {
        if (matrix[i][j].has_fruit())
          draw_square(j, i, ui_prop.scale_factor, ui_prop.fruit_color, win);
        if (matrix[i][j].has_body())
          draw_square(j, i, ui_prop.scale_factor, ui_prop.body_color, win);
        if (matrix[i][j].has_head())
          draw_square(j, i, ui_prop.scale_factor, ui_prop.head_color, win);
      }
    }
  }

  template <ui::Window window>
  void operator()(states::win const& state, window& win) const {
    (*this)(state.running_game, win);
  }

  template <ui::Window window>
  void operator()(states::lost const& state, window& win) const {
    (*this)(state.running_game, win);
  }

  template <ui::Window window>
  void operator()(auto const&, window&) const {}
};

template <ui::Window window>
void render(ui_renderer const& renderer, states::state const& state,
            window& win) {
  std::visit([&win, &renderer](auto const& s) { renderer(s, win); }, state);
  win.repaint();
}
}  // namespace snk
