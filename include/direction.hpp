#pragma once

#include <string_view>
namespace snk {
enum class direction_t { right, left, up, down };

inline direction_t opposite(direction_t dir) {
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

inline std::string_view to_string(direction_t dir) {
  switch (dir) {
  case direction_t::up:
    return "up";
  case direction_t::down:
    return "down";
  case direction_t::left:
    return "left";
  case direction_t::right:
    return "right";
  }
  return "up";// unreachable
}

}// namespace snk
