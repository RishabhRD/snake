#pragma once

namespace snk {
enum class direction { right, left, up, down };

// Postcondition:
//   - Returns oppisite direction of dir
constexpr direction opposite(direction dir) {
  switch (dir) {
    case direction::right:
      return direction::left;
    case direction::left:
      return direction::right;
    case direction::up:
      return direction::down;
    case direction::down:
      return direction::up;
  }
  return direction::up;  // unreachable
}
}  // namespace snk
