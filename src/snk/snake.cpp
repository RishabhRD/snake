#include "snake.hpp"
#include <algorithm>

namespace snk {
bool is_collided_to_self(snake_t const &snake) {
  return std::any_of(begin(snake.body_points()),
    std::prev(end(snake.body_points())),
    [&snake](auto pnt) { return pnt == snake.head(); });
}
}// namespace snk
