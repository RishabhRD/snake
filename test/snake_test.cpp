#include "board.hpp"
#include "test_include.hpp"
#include "point.hpp"
#include "snake.hpp"
#include "direction.hpp"

const suite snake_suite = [] {
  snk::board_t board{ 10, 10 };
  snk::snake_t old_snake{
    { { 3, 3 }, { 4, 3 } }, snk::direction_t::right, board
  };

  "increase length"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 3, 3 }, { 4, 3 }, { 5, 3 } }, snk::direction_t::right, board
    };
    expect(eq(old_snake.increase_len(), expected_snake));
  };

  "move"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 4, 3 }, { 5, 3 } }, snk::direction_t::right, board
    };
    expect(eq(old_snake.move(), expected_snake));
  };

  "change direction"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 3, 3 }, { 4, 3 } }, snk::direction_t::up, board
    };
    expect(
      eq(old_snake.set_cur_direction(snk::direction_t::up), expected_snake));
  };

  "change to opposite direction"_test = [=]() mutable {
    snk::snake_t expected_snake{ old_snake };
    old_snake.set_cur_direction(snk::direction_t::left);
    expect(eq(expected_snake, old_snake));
  };

  "move after changing direction"_test = [=]() mutable {
    snk::snake_t expected_snake{
      { { 4, 3 }, { 4, 2 } }, snk::direction_t::up, board
    };
    old_snake.set_cur_direction(snk::direction_t::up);
    expect(eq(old_snake.move(), expected_snake));
  };

  "collided to self"_test = [board] {
    snk::snake_t snake{ { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 }, { 1, 1 } },
      snk::direction_t::right,
      board };
    expect(eq(snk::is_collided_to_self(snake), true));
  };

  "not collided to self"_test = [board] {
    snk::snake_t snake{
      { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 } }, snk::direction_t::right, board
    };
    expect(eq(snk::is_collided_to_self(snake), false));
  };

  "head"_test = [=] {
    snk::snake_t snake{
      { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 } }, snk::direction_t::right, board
    };
    expect(eq(snake.head(), snk::point_t{ 2, 1 }));
  };

  "positive out of bounds movement"_test = [=]() mutable {
    snk::snake_t snake{
      { { 8, 3 }, { 9, 3 } }, snk::direction_t::right, board
    };
    snk::snake_t expected_snake{
      { { 9, 3 }, { 0, 3 } }, snk::direction_t::right, board
    };
    snake.move();
    expect(eq(snake, expected_snake));
  };

  "negative out of bounds movement"_test = [=]() mutable {
    snk::snake_t snake{ { { 1, 3 }, { 0, 3 } }, snk::direction_t::left, board };
    snk::snake_t expected_snake{
      { { 0, 3 }, { 9, 3 } }, snk::direction_t::left, board
    };
    snake.move();
    expect(eq(snake, expected_snake));
  };
};
