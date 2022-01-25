#include "board.hpp"
#include "rd/variant_then.hpp"
#include "snake.hpp"
#include "state.hpp"
#include "state_ops.hpp"
#include "test_include.hpp"

using namespace std::literals;

class mock_fruit_generator {
  std::list<snk::point_t> points_;

public:
  mock_fruit_generator(std::initializer_list<snk::point_t> points)
    : points_(points) {}

  auto operator()(snk::running_t const & /*unused*/) {
    auto obj = points_.front();
    points_.pop_front();
    return obj;
  }
};

class mock_now {
  std::list<std::chrono::time_point<std::chrono::system_clock>> times_;

public:
  mock_now(
    std::initializer_list<std::chrono::time_point<std::chrono::system_clock>>
      times)
    : times_(times) {}

  auto operator()() {
    auto obj = times_.front();
    times_.pop_front();
    return obj;
  }
};


suite const state_machine_suite = [] {
  "state after collision"_test = [] {
    snk::snake_t snake{
      { { 4, 5 }, { 5, 5 }, { 6, 5 }, { 6, 4 }, { 5, 4 }, { 4, 4 }, { 4, 5 } },
      snk::direction_t::east
    };
    snk::board_t board{ 10, 10 };
    snk::state_t state{ snk::running_t{ std::move(snake),
      { 2, 2 },
      board,
      10,
      std::chrono::system_clock::now() } };

    snk::check_collision(state);
    expect(rd::is<snk::finished_t>(state));
  };

  "state after not colliding"_test = [] {
    snk::snake_t snake{
      { { 4, 5 }, { 5, 5 }, { 6, 5 }, { 6, 4 }, { 5, 4 }, { 4, 4 } },
      snk::direction_t::east
    };
    snk::board_t board{ 10, 10 };
    snk::state_t state{ snk::running_t{ std::move(snake),
      { 2, 2 },
      board,
      10,
      std::chrono::system_clock::now() } };

    snk::check_collision(state);
    expect(rd::is<snk::running_t>(state));
  };

  "state after eating"_test = [] {
    snk::snake_t init_snake{ { { 3, 3 }, { 4, 3 }, { 5, 3 } },
      snk::direction_t::east };
    snk::board_t board{ 10, 10 };
    snk::running_t state{ std::move(init_snake),
      { 6, 3 },
      board,
      10,
      std::chrono::system_clock::now() };

    mock_fruit_generator next_fruit{ { 6, 5 }, { 5, 5 } };
    snk::snake_t &snake = state.snake();

    snake.move();
    snake.set_cur_direction(snk::direction_t::south);
    snk::try_eating(state, next_fruit);
    expect(eq(state.fruit_pos(), snk::point_t{ 6, 5 }));
    expect(eq(snake.size(), 4));
    expect(eq(snake.head(), snk::point_t{ 6, 4 }));

    snake.move();
    snake.set_cur_direction(snk::direction_t::west);
    snk::try_eating(state, next_fruit);
    expect(eq(state.fruit_pos(), snk::point_t{ 5, 5 }));
    expect(eq(snake.size(), 5));
    expect(eq(snake.head(), snk::point_t{ 5, 5 }));
  };

  "eating out of board food"_test = [] {
    snk::snake_t init_snake{ { { 3, 3 }, { 4, 3 }, { 5, 3 } },
      snk::direction_t::east };
    snk::board_t board{ 10, 10 };
    snk::running_t state{ std::move(init_snake),
      { 6, 3 },
      board,
      10,
      std::chrono::system_clock::now() };

    mock_fruit_generator next_fruit{ { 16, 5 }, { 5, 5 } };
    snk::snake_t &snake = state.snake();

    snake.move();
    snake.set_cur_direction(snk::direction_t::south);
    snk::try_eating(state, next_fruit);
    expect(eq(state.fruit_pos(), snk::point_t{ 16, 5 }));
    expect(eq(snake.size(), 4));
    expect(eq(snake.head(), snk::point_t{ 6, 4 }));

    snake.move();
    snake.set_cur_direction(snk::direction_t::west);
    snk::try_eating(state, next_fruit);
    expect(eq(state.fruit_pos(), snk::point_t{ 5, 5 }));
    expect(eq(snake.size(), 5));
    expect(eq(snake.head(), snk::point_t{ 5, 5 }));
  };

  "not eating a food"_test = [] {
    snk::snake_t init_snake{ { { 3, 3 }, { 4, 3 }, { 5, 3 } },
      snk::direction_t::east };
    snk::board_t board{ 10, 10 };
    snk::running_t state{ std::move(init_snake),
      { 6, 3 },
      board,
      10,
      std::chrono::system_clock::now() };

    mock_fruit_generator next_fruit{ { 16, 5 }, { 5, 5 } };
    snk::snake_t &snake = state.snake();

    snake.set_cur_direction(snk::direction_t::south);
    snk::try_eating(state, next_fruit);
    expect(eq(state.fruit_pos(), snk::point_t{ 6, 3 }));
    expect(eq(snake.size(), 3));
    expect(eq(snake.head(), snk::point_t{ 5, 3 }));
  };

  "movement after time passed"_test = [] {
    auto const speed = 10;
    auto const time_period = snk::to_time_period(speed);
    auto const init_time = std::chrono::system_clock::now();
    mock_now now{
      init_time, (init_time + 2 * time_period), (init_time + 4 * time_period)
    };
    snk::snake_t init_snake{ { { 3, 3 }, { 4, 3 }, { 5, 3 } },
      snk::direction_t::east };
    snk::board_t board{ 10, 10 };
    snk::running_t state{
      std::move(init_snake), { 6, 3 }, board, speed, now()
    };

    snk::snake_t &snake = state.snake();
    snk::try_moving_snake(state, now);
    expect(eq(snake.head(), snk::point_t{ 6, 3 }));
  };

  "movement after time not passed"_test = [] {
    auto const speed = 10;
    auto const time_period = snk::to_time_period(speed);
    auto const init_time = std::chrono::system_clock::now();
    mock_now now{
      init_time, (init_time + time_period / 2), (init_time + 4 * time_period)
    };
    snk::snake_t init_snake{ { { 3, 3 }, { 4, 3 }, { 5, 3 } },
      snk::direction_t::east };
    snk::board_t board{ 10, 10 };
    snk::running_t state{
      std::move(init_snake), { 6, 3 }, board, speed, now()
    };

    snk::snake_t &snake = state.snake();
    snk::try_moving_snake(state, now);
    expect(eq(snake.head(), snk::point_t{ 5, 3 }));
  };
};
