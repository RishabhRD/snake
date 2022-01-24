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

inline direction_t opposite_direction(direction_t dir){
  switch(dir) {
    case direction_t::east : return direction_t::west;
    case direction_t::west : return direction_t::east;
    case direction_t::north : return direction_t::south;
    case direction_t::south : return direction_t::north;
  }
  throw "Unreachable";
}

}// namespace snk
