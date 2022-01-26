#pragma once
#include "board.hpp"
#include "input.hpp"
#include "point.hpp"
#include "snake.hpp"
#include <utility>
#include <variant>
#include <chrono>
#include <vector>

namespace snk {
struct init_t {};

class running_t {
  snake_t snake_;
  point_t fruit_pos_;
  std::chrono::time_point<std::chrono::system_clock> last_tick_;
  std::size_t speed_;
  std::vector<snk::direction_input_t> queued_direction_inputs_;

public:
  explicit running_t(snake_t snake,
    point_t fruit_pos,
    std::size_t speed,
    std::chrono::time_point<std::chrono::system_clock> last_tick)
    : snake_(std::move(snake)), fruit_pos_(fruit_pos), last_tick_(last_tick),
      speed_(speed) {}

  auto snake() -> snake_t & { return snake_; }
  [[nodiscard]] auto snake() const -> const snake_t & { return snake_; }

  [[nodiscard]] auto fruit_pos() const { return fruit_pos_; }
  auto fruit_pos(point_t new_pos) { fruit_pos_ = new_pos; }

  [[nodiscard]] auto last_tick() const { return last_tick_; }
  auto last_tick(std::chrono::time_point<std::chrono::system_clock> tick) {
    last_tick_ = tick;
  }

  [[nodiscard]] auto board() const { return snake_.board(); }

  [[nodiscard]] auto speed() const { return speed_; }
  auto speed(std::size_t speed) { speed_ = speed; }

  [[nodiscard]] auto score() const { return snake_.size(); }

  [[nodiscard]] auto queued_direction_inputs() const
    -> std::vector<snk::direction_input_t> const & {
    return queued_direction_inputs_;
  }

  [[nodiscard]] auto queued_direction_inputs()
    -> std::vector<snk::direction_input_t> & {
    return queued_direction_inputs_;
  }
};

class finished_t {
  std::size_t score_;

public:
  explicit finished_t(std::size_t score) : score_(score) {}
  [[nodiscard]] auto score() const { return score_; }
};

class closed_t {};

using state_t = std::variant<init_t, running_t, finished_t, closed_t>;
}// namespace snk
