#pragma once

#include <vector>
#include "event.hpp"

namespace snk::ui {
template <typename T>
concept Window = requires(T& win, T const& c_win) {
  { width(c_win) } -> std::same_as<std::size_t>;
  { height(c_win) } -> std::same_as<std::size_t>;
  { poll_events(win) } -> std::same_as<std::vector<events::event>>;
};
}  // namespace snk::ui
