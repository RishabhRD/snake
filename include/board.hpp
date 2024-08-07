#pragma once

#include "point.hpp"
#include "snake.hpp"
#include "mod_int.hpp"
#include <cstddef>
namespace snk {
// TODO: I couldn't find any invariants this class can hold in a convincing
// way. There is surely some constraints like fruit should be inside board
// dimensions only. However, I don't know how to express them.
// Feel free to raise a PR if you can figure it out or an issue if you can
// justify the current decision :)
struct board {
  std::size_t const width;
  std::size_t const height;
  snk::snake<mod_int> snake;
  snk::point<std::size_t> fruit_pos;
};

enum class board_pos_info {
  empty,
  snake,
  fruit,
};
}// namespace snk
