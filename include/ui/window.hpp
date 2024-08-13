#pragma once

#include <string_view>
#include <vector>
#include "event.hpp"
#include "ui/color.hpp"

namespace snk::ui {
template <typename T>
concept Window = requires(T& win, T const& c_win, std::size_t x, std::size_t y,
                          std::size_t size, color c, std::string_view path) {
  { c_win.width() } -> std::same_as<std::size_t>;
  { c_win.height() } -> std::same_as<std::size_t>;
  { win.poll_events() } -> std::same_as<std::vector<events::event>>;
  { win.draw_square(x, y, size, c) };
  { win.draw_image(path) } -> std::same_as<bool>;
  { win.repaint() };
  { win.clear(c) };
};
}  // namespace snk::ui
