#pragma once

#include <string_view>
#include <vector>
#include "event.hpp"
#include "ui/color.hpp"

namespace snk::ui {
template <typename T>
concept Window = requires(T& win, T const& c_win, std::size_t x, std::size_t y,
                          color c, std::string_view path) {
  { c_win.width() } -> std::same_as<std::size_t>;
  { c_win.height() } -> std::same_as<std::size_t>;
  { win.poll_events() } -> std::same_as<std::vector<events::event>>;
  { win.set_pixel_color(x, y, c) };
  { win.draw_image(path) } -> std::same_as<bool>;
  { win.repaint() };
};
}  // namespace snk::ui
