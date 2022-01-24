#pragma once

#include <string_view>
namespace snk {
enum class direction_t { east, west, north, south };

inline std::string_view to_string(direction_t dir) {
  using namespace std::literals;
  switch (dir) {
  case direction_t::east:
    return "EAST";
  case direction_t::west:
    return "WEST";
  case direction_t::north:
    return "NORTH";
  case direction_t::south:
    return "SOUTH";
  }
  throw "Unreachable";
}

}// namespace snk
