#pragma once

namespace snk {
enum class direction_t { right, left, up, down };

// Postcondition:
//   - Returns oppisite direction of dir
constexpr direction_t opposite(direction_t dir) {
  switch (dir) {
  case direction_t::right:
    return direction_t::left;
  case direction_t::left:
    return direction_t::right;
  case direction_t::up:
    return direction_t::down;
  case direction_t::down:
    return direction_t::up;
  }
  return direction_t::up;// unreachable
}
}// namespace snk
