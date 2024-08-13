#pragma once

#include <vector>
#include "event.hpp"

namespace snk::ui {
template <typename T>
concept Window = requires(T& win, T const& c_win) {
  { c_win.width() } -> std::same_as<std::size_t>;
  { c_win.height() } -> std::same_as<std::size_t>;
  { c_win.poll_events() } -> std::same_as<std::vector<events::event>>;
};
}  // namespace snk::ui
