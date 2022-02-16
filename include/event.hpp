#pragma once
#include "direction.hpp"
#include <optional>
#include <variant>

namespace snk::event {
enum class direction_change { left, right, up, down };

inline auto to_direction(direction_change input) {
  switch (input) {
  case direction_change::left:
    return direction_t::west;
  case direction_change::right:
    return direction_t::east;
  case direction_change::up:
    return direction_t::north;
  case direction_change::down:
    return direction_t::south;
  }
  return direction_t::north;
}

struct quit {};

struct play_pause {};

struct start {};

using event_t = std::variant<direction_change, quit, play_pause, start>;
}// namespace snk::event
