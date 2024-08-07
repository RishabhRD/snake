#pragma once

#include "point.hpp"
#include "snake.hpp"
#include "mod_int.hpp"
#include <cstddef>
namespace snk {
// TODO: I couldn't find any invariants this class can hold in a convincing
// way. There is surely some constraints like fruit should be inside board
// dimensions only. However, don't know how to express them.
// Feel free to raise a PR if you can figure it out or an issue if you can
// justify the current decision :)
struct board {
  std::size_t height;
  std::size_t width;
  snake<mod_int> snake;
  point<mod_int> fruit_pos;
};
}// namespace snk
