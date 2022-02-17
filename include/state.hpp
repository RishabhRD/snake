#pragma once
#include "board.hpp"
#include "event.hpp"
#include "point.hpp"
#include "snake.hpp"
#include <utility>
#include <variant>
#include <chrono>
#include <vector>

namespace snk {
struct init_t {
  friend auto operator==(const init_t &, const init_t &) -> bool = default;
};

class running_t {
  snake_t snake_;
  point_t fruit_pos_;
  std::chrono::time_point<std::chrono::system_clock> last_tick_;
  std::size_t speed_;
  std::vector<snk::event::direction_change> queued_direction_inputs_;

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

  [[nodiscard]] auto with_last_tick(
    std::chrono::time_point<std::chrono::system_clock> tick)
    const & -> running_t {
    running_t state{ *this };
    state.last_tick_ = tick;
    return state;
  }

  [[nodiscard]] auto with_last_tick(
    std::chrono::time_point<std::chrono::system_clock> tick) && -> running_t {
    running_t state{ std::move(*this) };
    state.last_tick_ = tick;
    return state;
  }

  [[nodiscard]] auto board() const { return snake_.board(); }

  [[nodiscard]] auto speed() const { return speed_; }

  [[nodiscard]] auto with_speed(std::size_t speed) const & -> running_t {
    auto self{ *this };
    self.speed_ = speed;
    return self;
  }

  [[nodiscard]] auto with_speed(std::size_t speed) && -> running_t {
    auto self{ std::move(*this) };
    self.speed_ = speed;
    return self;
  }

  [[nodiscard]] auto score() const { return snake_.size(); }

  [[nodiscard]] auto queued_direction_inputs() const
    -> std::vector<snk::event::direction_change> const & {
    return queued_direction_inputs_;
  }

  [[nodiscard]] auto queued_direction_inputs()
    -> std::vector<snk::event::direction_change> & {
    return queued_direction_inputs_;
  }

  friend auto operator==(const running_t &, const running_t &)
    -> bool = default;
};

class finished_t {
  std::size_t score_;

public:
  explicit finished_t(std::size_t score) : score_(score) {}
  [[nodiscard]] auto score() const { return score_; }

  friend auto operator==(const finished_t &, const finished_t &)
    -> bool = default;
};

class closed_t {
  friend auto operator==(const closed_t &, const closed_t &) -> bool = default;
};

class paused_t {
  snk::running_t running_state_;

public:
  explicit paused_t(snk::running_t running)
    : running_state_{ std::move(running) } {};

  [[nodiscard]] auto running_state() const { return running_state_; }

  friend auto operator==(const paused_t &, const paused_t &) -> bool = default;
};

using state_t = std::variant<init_t, running_t, paused_t, finished_t, closed_t>;
}// namespace snk
