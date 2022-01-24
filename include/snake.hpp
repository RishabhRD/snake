#pragma once

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

public:
  explicit snake_t(std::initializer_list<point_t> body_points, direction_t dir)
    : body_points_(body_points), cur_direction_(dir) {}


  [[nodiscard]] std::size_t size() const { return body_points_.size(); }

  [[nodiscard]] direction_t cur_direction() const { return cur_direction_; }

  [[nodiscard]] const std::list<point_t> &body_points() const {
    return body_points_;
  }

  [[nodiscard]] auto head() const { return body_points_.back(); }

  auto increase_len() -> snake_t & {
    auto head = body_points_.back();
    body_points_.push_back(next_point_in_direction(head, cur_direction_));
    return *this;
  }

  auto move() -> snake_t & {
    auto head = body_points_.back();
    body_points_.push_back(next_point_in_direction(head, cur_direction_));
    body_points_.pop_front();
    return *this;
  }

  auto set_cur_direction(direction_t dir) -> snake_t & {
    if (dir == opposite_direction(cur_direction_)) return *this;
    cur_direction_ = dir;
    return *this;
  }

  friend bool operator==(const snake_t &, const snake_t &) = default;

  friend std::ostream &operator<<(std::ostream &out, snake_t const &snake) {
    out << '[';
    out << '{';
    for (auto p : snake.body_points_) out << ' ' << p << ' ';
    out << '}';
    out << ' ';
    out << to_string(snake.cur_direction_) << ']';
    return out;
  }
};

bool is_collided_to_self(snake_t const &snake);

}// namespace snk
