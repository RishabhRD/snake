#pragma once

#include <iostream>
#include <variant>
#include "property.hpp"
#include "state.hpp"
#include "ui/window.hpp"

namespace snk {

struct ui_renderer {
  ui_properties ui_prop;

  template <ui::Window window>
  void operator()(states::init, window& win) const {
    if (!win.draw_image("data/title.png")) {
      std::cerr << "Can't load backgound\n";
    }
  }

  template <ui::Window window>
  void operator()(auto const&, window&) const {
    std::cerr << "TODO: implement this" << std::endl;
  }
};

template <ui::Window window>
void render(ui_renderer const& renderer, states::state const& state,
            window& win) {
  std::visit([&win, &renderer](auto const& s) { renderer(s, win); }, state);
  win.repaint();
}
}  // namespace snk
