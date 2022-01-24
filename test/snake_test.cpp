#include "test_include.hpp"
#include "point.hpp"
#include "snake.hpp"
#include "direction.hpp"

const suite snake_suite = [] {
  snk::snake_t old_snake{ { { 3, 3 }, { 3, 4 } }, snk::direction_t::east };

  "increase length"_test = [=]() mutable {
    snk::snake_t expected_snake{ { { 3, 3 }, { 3, 4 }, { 3, 5 } },
      snk::direction_t::east };
    expect(eq(old_snake.increase_len(), expected_snake));
  };

  "move"_test = [=]() mutable {
    snk::snake_t expected_snake{ { { 3, 4 }, { 3, 5 } },
      snk::direction_t::east };
    expect(eq(old_snake.move(), expected_snake));
  };

  "change direction"_test = [=]() mutable {
    snk::snake_t expected_snake{ { { 3, 3 }, { 3, 4 } },
      snk::direction_t::north };
    expect(
      eq(old_snake.set_cur_direction(snk::direction_t::north), expected_snake));
  };

  "change to opposite direction"_test = [=]() mutable {
    snk::snake_t expected_snake{ old_snake };
    old_snake.set_cur_direction(snk::direction_t::west);
    expect(eq(expected_snake, old_snake));
  };

  "move after changing direction"_test = [=]() mutable {
    snk::snake_t expected_snake{ { { 3, 4 }, { 2, 4 } },
      snk::direction_t::north };
    old_snake.set_cur_direction(snk::direction_t::north);
    expect(eq(old_snake.move(), expected_snake));
  };

  "collided to self"_test = [] {
    snk::snake_t snake{ { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 }, { 1, 1 } },
      snk::direction_t::east };
    expect(eq(snk::is_collided_to_self(snake), true));
  };

  "not collided to self"_test = [] {
    snk::snake_t snake{ { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 } },
      snk::direction_t::east };
    expect(eq(snk::is_collided_to_self(snake), false));
  };

  "head"_test = [] {
    snk::snake_t snake{ { { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 } },
      snk::direction_t::east };
    expect(eq(snake.head(), snk::point_t{ 2, 1 }));
  };
};
