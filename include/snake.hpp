#pragma once

#include "board.hpp"
#include "board_point_ops.hpp"
#include "ostream"
#include "direction.hpp"
#include "point.hpp"
#include "point_dir_ops.hpp"
#include <initializer_list>
#include <list>

namespace snk {
class snake_t {
  // snake points all the points of snake
  // head of snake is the back of list
  // tail of snake is front of list
  std::list<point_t> body_points_;
  direction_t cur_direction_;
  board_t board_;

public:
  explicit snake_t(std::initializer_list<point_t> body_points,
    direction_t dir,
    board_t board)
    : body_points_(body_points), cur_direction_(dir), board_(board) {}


  [[nodiscard]] auto size() const -> std::size_t { return body_points_.size(); }

  [[nodiscard]] auto cur_direction() const -> direction_t {
    return cur_direction_;
  }

  [[nodiscard]] auto body_points() const -> const std::list<point_t> & {
    return body_points_;
  }

  [[nodiscard]] auto head() const { return body_points_.back(); }

  [[nodiscard]] auto board() const { return board_; }

  auto increase_len() -> snake_t & {
    auto head = body_points_.back();
    body_points_.push_back(
      snk::in_board(next_point_in_direction(head, cur_direction_), board_));
    return *this;
  }

  auto move() -> snake_t & {
    auto head = body_points_.back();
    body_points_.push_back(
      snk::in_board(next_point_in_direction(head, cur_direction_), board_));
    body_points_.pop_front();
    return *this;
  }

  auto set_cur_direction(direction_t const dir) -> snake_t & {
    if (dir == opposite_direction(cur_direction_)) return *this;
    cur_direction_ = dir;
    return *this;
  }

  friend auto operator==(snake_t const &, snake_t const &) -> bool = default;

  friend auto operator<<(std::ostream &out, snake_t const &snake)
    -> std::ostream & {
    out << '[';
    out << '{';
    for (auto p : snake.body_points_) out << ' ' << p << ' ';
    out << '}';
    out << ' ';
    out << to_string(snake.cur_direction_) << ']';
    return out;
  }
};

auto is_collided_to_self(snake_t const &snake) -> bool;

}// namespace snk
