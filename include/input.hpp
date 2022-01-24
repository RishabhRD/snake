#pragma once
#include "direction.hpp"
#include "tl/optional.hpp"

namespace snk {
enum class input_t { left, right, up, down, quit };

inline auto to_direction(input_t input) -> tl::optional<direction_t> {
  switch (input) {
  case input_t::left:
    return direction_t::west;
  case input_t::right:
    return direction_t::east;
  case input_t::up:
    return direction_t::north;
  case input_t::down:
    return direction_t::south;
  default:
    return tl::nullopt;
  }
}
}// namespace snk
