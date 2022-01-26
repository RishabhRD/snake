#include "board_point_ops.hpp"
#include "event_input_ops.hpp"
#include "init_game_data.hpp"
#include "point.hpp"
#include "snake.hpp"
#include "state.hpp"
#include "state_ops.hpp"
#include "input_handler.hpp"
#include "rd/variant_then.hpp"
#include "rd/overload.hpp"
#include <algorithm>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>


class pixel_converter_t {
  int scaling_factor_x_;
  int scaling_factor_y_;

public:
  pixel_converter_t(int scaling_factor_x, int scaling_factor_y)
    : scaling_factor_x_(scaling_factor_x), scaling_factor_y_(scaling_factor_y) {
  }

  [[nodiscard]] auto operator()(snk::point_t point) const -> sf::Vector2f {
    return { static_cast<float>(point.x * scaling_factor_x_),
      static_cast<float>(point.y * scaling_factor_y_) };
  }
};


auto poll_events(sf::RenderWindow &window, snk::state_t &game_state) {
  sf::Event event{};
  while (window.pollEvent(event)) {
    auto opt_input = snk::to_input(event);
    if (opt_input) snk::handle_input(*opt_input, game_state);
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

void draw_snake_head(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  draw_tile(state.snake().head(), sf::Color::Blue, window, to_pixel);
}

void draw_snake_body(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  std::for_each(begin(state.snake().body_points()),
    std::prev(end(state.snake().body_points())),
    [&](auto body_point) {
      draw_tile(body_point, sf::Color::Green, window, to_pixel);
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
  draw_tile(state.fruit_pos(), sf::Color::Red, window, to_pixel);
}

void draw(sf::RenderWindow &window,
  snk::running_t const &state,
  pixel_converter_t const to_pixel) {
  window.clear(sf::Color::Black);
  draw_fruit(window, state, to_pixel);
  draw_snake(window, state, to_pixel);
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

auto main() -> int {
  sf::RenderWindow window(
    sf::VideoMode(snk::game_data::win_size_x, snk::game_data::win_size_y),
    "Snake",
    sf::Style::None);
  snk::state_t game_state{ snk::init_t{} };
  while (window.isOpen()) {// NOLINT
    poll_events(window, game_state);
    if (rd::is<snk::closed_t>(game_state)) window.close();
    snk::after_time_period(game_state, [](snk::state_t &state) {
      rd::then<snk::running_t>(state, snk::try_eating);
      snk::process_queued_directions(state);
      rd::then<snk::running_t>(state, snk::move_snake);
      if (rd::is<snk::running_t>(state)) snk::check_collision(state);
    });
    draw(window,
      game_state,
      pixel_converter_t{
        snk::game_data::scaling_factor_x, snk::game_data::scaling_factor_y });
    window.display();
    using namespace std::literals;
    std::this_thread::sleep_for(50ms);
  }
  return 0;
}
