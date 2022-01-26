#pragma once
#include "direction.hpp"
#include <optional>
#include <variant>

namespace snk {
enum class direction_input_t { left, right, up, down };

inline auto to_direction(direction_input_t input) {
  switch (input) {
  case direction_input_t::left:
    return direction_t::west;
  case direction_input_t::right:
    return direction_t::east;
  case direction_input_t::up:
    return direction_t::north;
  case direction_input_t::down:
    return direction_t::south;
  }
  return direction_t::north;
}

struct quit_input_t {};

struct play_pause_input_t {};

struct start_input_t {};

using input_t = std::
  variant<direction_input_t, quit_input_t, play_pause_input_t, start_input_t>;
}// namespace snk
