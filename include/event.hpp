#pragma once
#include "direction.hpp"
#include "point.hpp"
#include <optional>
#include <variant>
#include <chrono>

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

struct start {
  std::chrono::time_point<std::chrono::system_clock> cur_time;
};

struct timeout {
  std::chrono::time_point<std::chrono::system_clock> cur_time;
};

struct fruit_generated {
  point_t fruit_pos;
};

using event_t = std::
  variant<direction_change, quit, play_pause, start, timeout, fruit_generated>;
}// namespace snk::event
