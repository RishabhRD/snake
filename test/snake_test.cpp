#include "board.hpp"
#include "test_include.hpp"
#include "point.hpp"
#include "snake.hpp"
#include "direction.hpp"

const suite snake_suite = [] {
  snk::board_t board{ 10, 10 };
  snk::snake_t old_snake{
    { { 3, 3 }, { 4, 3 } }, snk::direction_t::east, board
  };

  "increase length"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 3, 3 }, { 4, 3 }, { 5, 3 } }, snk::direction_t::east, board
    };
    expect(eq(old_snake.increase_len(), expected_snake));
  };

  "move"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 4, 3 }, { 5, 3 } }, snk::direction_t::east, board
    };
    expect(eq(old_snake.move(), expected_snake));
  };

  "change direction"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 3, 3 }, { 4, 3 } }, snk::direction_t::north, board
    };
    expect(
      eq(old_snake.set_cur_direction(snk::direction_t::north), expected_snake));
  };

  "change to opposite direction"_test = [=]() mutable {
    snk::snake_t expected_snake{ old_snake };
    old_snake.set_cur_direction(snk::direction_t::west);
    expect(eq(expected_snake, old_snake));
  };

  "move after changing direction"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 4, 3 }, { 4, 2 } }, snk::direction_t::north, board
    };
    old_snake.set_cur_direction(snk::direction_t::north);
    expect(eq(old_snake.move(), expected_snake));
  };

  "collided to self"_test = [board] {
    snk::snake_t snake{ { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 }, { 1, 1 } },
      snk::direction_t::east,
      board };
    expect(eq(snk::is_collided_to_self(snake), true));
  };

  "not collided to self"_test = [board] {
    snk::snake_t snake{
      { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 } }, snk::direction_t::east, board
    };
    expect(eq(snk::is_collided_to_self(snake), false));
  };

  "head"_test = [=] {
    snk::snake_t snake{
      { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 } }, snk::direction_t::east, board
    };
    expect(eq(snake.head(), snk::point_t{ 2, 1 }));
  };

  "positive out of bounds movement"_test = [=]() mutable {
    snk::snake_t snake{ { { 8, 3 }, { 9, 3 } }, snk::direction_t::east, board };
    snk::snake_t expected_snake{
      { { 9, 3 }, { 0, 3 } }, snk::direction_t::east, board
    };
    snake.move();
    expect(eq(snake, expected_snake));
  };

  "negative out of bounds movement"_test = [=]() mutable {
    snk::snake_t snake{ { { 1, 3 }, { 0, 3 } }, snk::direction_t::west, board };
    snk::snake_t expected_snake{
      { { 0, 3 }, { 9, 3 } }, snk::direction_t::west, board
    };
    snake.move();
    expect(eq(snake, expected_snake));
  };
};
