#pragma once

#include <chrono>
#include <variant>
#include "board.hpp"
#include "direction.hpp"

namespace snk::states {
struct running {
  snk::board board;
  snk::direction cur_snake_dir;
  snk::direction next_snake_dir;
  std::chrono::milliseconds time_since_last_move;
  std::chrono::milliseconds move_threshold;

  friend bool operator==(running const&, running const&) = default;
};

struct paused {
  running running_game;
  friend bool operator==(paused const&, paused const&) = default;
};

struct init {
  friend bool operator==(init const&, init const&) = default;
};

struct quit {
  friend bool operator==(quit const&, quit const&) = default;
};

struct lost {
  running running_game;
  friend bool operator==(lost const&, lost const&) = default;
};

struct win {
  running running_game;
  friend bool operator==(win const&, win const&) = default;
};

using state = std::variant<running, paused, init, quit, lost, win>;
}  // namespace snk::states
