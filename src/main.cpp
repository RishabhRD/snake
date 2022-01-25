#include "board_point_ops.hpp"
#include "event_input_ops.hpp"
#include "point.hpp"
#include "snake.hpp"
#include "state.hpp"
#include "state_ops.hpp"
#include "input_handler.hpp"
#include "rd/variant_then.hpp"
#include "rd/overload.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>


class pixel_converter_t {
  std::size_t scaling_factor_x_;
  std::size_t scaling_factor_y_;

public:
  pixel_converter_t(std::size_t scaling_factor_x, std::size_t scaling_factor_y)
    : scaling_factor_x_(scaling_factor_x), scaling_factor_y_(scaling_factor_y) {
  }

  [[nodiscard]] sf::Vector2f operator()(snk::point_t point) const {
    return { static_cast<float>(point.y * scaling_factor_y_),
      static_cast<float>(point.x * scaling_factor_x_) };
  }
};


void poll_events(sf::RenderWindow &window, snk::state_t &state) {
  sf::Event event{};
  while (window.pollEvent(event)) {
    auto opt_input = snk::to_input(event);
    if (opt_input) snk::handle_input(*opt_input, state);
  }
}

void draw_tile(snk::point_t const position,
  sf::Color const &color,
  sf::RenderWindow &window,
  pixel_converter_t const to_pixel) {
  sf::RectangleShape rect{ to_pixel({ 1, 1 }) };
  rect.setFillColor(color);
  rect.setPosition(to_pixel(position));
  window.draw(rect);
}

void draw_tile_in_board(snk::point_t const position,
  sf::Color const &color,
  snk::board_t const board,
  sf::RenderWindow &window,
  pixel_converter_t const to_pixel) {
  auto const point_in_board = snk::in_board(position, board);
  draw_tile(point_in_board, color, window, to_pixel);
}

void draw_snake_head(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  draw_tile_in_board(
    state.snake().head(), sf::Color::Blue, state.board(), window, to_pixel);
}

void draw_snake_body(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  std::for_each(begin(state.snake().body_points()),
    std::prev(end(state.snake().body_points())),
    [&](auto body_point) {
      draw_tile_in_board(
        body_point, sf::Color::Green, state.board(), window, to_pixel);
    });
}

void draw_snake(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  draw_snake_head(window, state, to_pixel);
  draw_snake_body(window, state, to_pixel);
}

void draw_fruit(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  draw_tile_in_board(
    state.fruit_pos(), sf::Color::Red, state.board(), window, to_pixel);
}

void draw(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  window.clear(sf::Color::Black);
  draw_snake(window, state, to_pixel);
  draw_fruit(window, state, to_pixel);
}

void draw(sf::RenderWindow &window,
  snk::state_t const &game_state,
  pixel_converter_t const to_pixel) {
  auto draw_states = rd::overload{ [&](snk::running_t const &state) {
                                    draw(window, state, to_pixel);
                                  },
    [](auto const &) {} };
  std::visit(std::move(draw_states), game_state);
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
    rd::then<snk::running_t>(state, snk::try_moving_snake, snk::try_eating);
    if (rd::is<snk::running_t>(state)) snk::check_collision(state);
    draw(
      window, state, pixel_converter_t{ scaling_factor_x, scaling_factor_y });
    window.display();
  }
  return 0;
}
