#include "snake_arithmetic.hpp"
#include "direction.hpp"
#include "doctest.hpp"
#include "point.hpp"
#include "snake.hpp"

test("is_collided_to_self") {
  snk::snake snake{snk::point{0, 0}};
  snake.grow(snk::direction::right);
  snake.grow(snk::direction::right);
  snake.move(snk::direction::left);
  req(snk::is_collided_to_self(snake));
}
