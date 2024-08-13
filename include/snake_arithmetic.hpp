#pragma once

#include <iterator>
#include "point.hpp"
#include "snake.hpp"

namespace snk {
// Postcondition:
//   - Returns true if head overlaps with any point from [begin, end)
template <Coordinate CoordType, typename Iter>
  requires std::same_as<std::iter_value_t<Iter>, point<CoordType>>
auto is_collided_to(snk::snake<CoordType> const& snake, Iter begin, Iter end) {
  auto head = snake.head();
  auto head_pos_itr = std::find(begin, end, head);
  return head_pos_itr != end;
}

// Postcondition:
//   - Returns true if head overlaps with any other part of body
template <Coordinate CoordType>
auto is_collided_to_self(snk::snake<CoordType> const& snake) {
  auto body = snake.body();
  return is_collided_to(snake, body.begin(), std::prev(body.end()));
}
}  // namespace snk
