#include <SFML/Window/WindowStyle.hpp>
#include <algorithm>
#include <random>
#include "board_point_ops.hpp"
#include "event_input_ops.hpp"
#include "input.hpp"
#include "point.hpp"
#include "snake.hpp"
#include "state.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random_point.hpp>
#include <rd/overload.hpp>
#include <variant>
#include <rd/variant_then.hpp>

auto random_point = snk::random_point_generator_t{};// NOLINT

auto random_fruit_for(snk::running_t const &state) -> snk::point_t {
  auto pnt = random_point();
  while (true) {
    if (std::none_of(begin(state.snake().body_points()),
          end(state.snake().body_points()),
          [pnt, &state](auto p) {
            return snk::in_board(p, state.board())
                   == snk::in_board(pnt, state.board());
          }))
      break;
    pnt = random_point();
  }
  return pnt;
}

class pixel_converter_t {
  std::size_t scaling_factor_x_;
  std::size_t scaling_factor_y_;

public:
  pixel_converter_t(std::size_t scaling_factor_x, std::size_t scaling_factor_y)
    : scaling_factor_x_(scaling_factor_x), scaling_factor_y_(scaling_factor_y) {
  }

  [[nodiscard]] sf::Vector2f operator()(snk::point_t point) const {
    return { static_cast<float>(point.x * scaling_factor_x_),
      static_cast<float>(point.y * scaling_factor_y_) };
  }
};

auto handle_quit(snk::state_t &state) { state = snk::closed_t{}; }

auto handle_dir(snk::running_t &state, snk::input_t input) {
  state.snake().set_cur_direction(*snk::to_direction(input));
}

auto handle_input(snk::input_t input, snk::state_t &state) {
  switch (input) {
  case snk::input_t::quit:
    handle_quit(state);
    break;
  case snk::input_t::down:
  case snk::input_t::up:
  case snk::input_t::right:
  case snk::input_t::left:
    rd::then<snk::running_t>(
      state, [input](snk::running_t &st) { handle_dir(st, input); });
    break;
  }
}

void poll_events(sf::RenderWindow &window, snk::state_t &state) {
  sf::Event event{};
  while (window.pollEvent(event)) {
    auto opt_input = snk::to_input(event);
    if (opt_input) handle_input(*opt_input, state);
  }
}

void draw(sf::RenderWindow & /*unused*/,
  snk::running_t const & /*unused*/,
  pixel_converter_t /*unused*/) {}

void draw(sf::RenderWindow &window,
  snk::state_t const &game_state,
  pixel_converter_t to_pixel) {
  auto draw_states = rd::overload{ [&](snk::running_t const &state) {
                                    draw(window, state, to_pixel);
                                  },
    [](auto const &) {} };
  std::visit(std::move(draw_states), game_state);
}

auto to_time_period(std::size_t speed) {
  using namespace std::literals;
  return 1000ms / (speed + 1);
}

auto time_passed_from(
  std::chrono::time_point<std::chrono::system_clock> time_point) {
  return std::chrono::system_clock::now() - time_point;
}

auto try_moving_snake(snk::running_t &state) {
  auto const movement_time_period = to_time_period(state.speed());
  auto const time_passed = time_passed_from(state.last_tick());
  if (time_passed >= movement_time_period) {
    state.snake().move();
    state.last_tick(std::chrono::system_clock::now());
  }
}

auto try_eating(snk::running_t &state) {
  if (state.snake().head() == state.fruit_pos()) {
    state.snake().increase_len();
    state.fruit_pos(random_fruit_for(state));
  }
}

auto check_collision(snk::state_t &state) {
  auto const &running_state = std::get<snk::running_t>(state);
  if (snk::is_collided_to_self(running_state.snake()))
    state = snk::finished_t{ running_state.score() };
}


int main() {
  constexpr static std::size_t num_tiles_x = 20;
  constexpr static std::size_t num_tiles_y = 20;
  constexpr static std::size_t scaling_factor_x = 30;
  constexpr static std::size_t scaling_factor_y = 30;
  constexpr static std::size_t win_size_x = scaling_factor_x * num_tiles_x;
  constexpr static std::size_t win_size_y = scaling_factor_y * num_tiles_y;
  snk::board_t board{ num_tiles_y, num_tiles_x };
  snk::snake_t init_snake{ { { 10, 9 }, { 10, 10 }, { 10, 11 } },
    snk::direction_t::east };
  snk::state_t state{ snk::running_t{
    std::move(init_snake), { 10, 17 }, board, 10 } };

  sf::RenderWindow window(
    sf::VideoMode(win_size_y, win_size_x), "Snake", sf::Style::None);
  while (window.isOpen()) {// NOLINT
    poll_events(window, state);
    if (rd::is<snk::closed_t>(state)) window.close();
    rd::then<snk::running_t>(state, try_moving_snake, try_eating);
    if (rd::is<snk::running_t>(state)) check_collision(state);
    draw(
      window, state, pixel_converter_t{ scaling_factor_x, scaling_factor_y });
  }
  return 0;
}
