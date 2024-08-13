#pragma once

#include <chrono>
#include "board.hpp"
#include "direction.hpp"

namespace snk::states {
struct running {
  snk::board board;
  snk::direction cur_snake_dir;
  std::chrono::milliseconds time_since_last_move;
  std::size_t speed;

  friend constexpr bool operator==(running const&, running const&);
};

struct paused {
  running running_game;
  friend constexpr bool operator==(paused const&, paused const&);
};

struct init {
  friend constexpr bool operator==(init const&, init const&);
};
}  // namespace snk::states
