#pragma once
#include "board.hpp"
#include "point.hpp"
#include "snake.hpp"
#include <utility>
#include <variant>
#include <chrono>

namespace snk {
struct init_t {};

class running_t {
  snake_t snake_;
  point_t fruit_pos_;
  std::chrono::time_point<std::chrono::system_clock> last_tick_;
  board_t board_;

public:
  explicit running_t(snake_t snake, point_t fruit_pos, board_t board)
    : snake_(std::move(snake)), fruit_pos_(fruit_pos),
      last_tick_(std::chrono::system_clock::now()), board_(board) {}

  auto snake() -> snake_t & { return snake_; }
  [[nodiscard]] auto snake() const -> const snake_t & { return snake_; }

  [[nodiscard]] auto fruit_pos() const { return fruit_pos_; }
  auto fruit_pos(point_t new_pos) { fruit_pos_ = new_pos; }

  [[nodiscard]] auto last_tick() const { return last_tick_; }
  auto last_tick(std::chrono::time_point<std::chrono::system_clock> tick) {
    last_tick_ = tick;
  }

  [[nodiscard]] auto board() const { return board_; }
};

class finished_t {
  int score_;

public:
  [[nodiscard]] int score() const { return score_; }
};

using state_t = std::variant<init_t, running_t, finished_t>;
}// namespace snk
