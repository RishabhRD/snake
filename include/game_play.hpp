#pragma once

#include "board_point_ops.hpp"
#include "event_input_ops.hpp"
#include "functional.hpp"
#include "init_game_data.hpp"
#include "point.hpp"
#include "random_fruit_generator.hpp"
#include "running_state_ops.hpp"
#include "snake.hpp"
#include "state.hpp"
#include "event_handler.hpp"
#include "rd/variant_then.hpp"
#include <boost/hof.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <span>

namespace snk {

auto pixel_on_draw_board(snk::bounded_point_t point) -> sf::Vector2f {
  return { static_cast<float>(point.x * snk::game_data::scaling_factor_x),
    static_cast<float>(point.y * snk::game_data::scaling_factor_y) };
}

auto poll_events(sf::RenderWindow &window, snk::state_t const &game_state) {
  std::vector<snk::event::event_t> events;
  sf::Event event{};
  if (rd::is<snk::running_t>(game_state)) {
    auto const cur_time = std::chrono::system_clock::now();
    if (snk::should_move(std::get<snk::running_t>(game_state), cur_time)) {
      events.emplace_back(snk::event::timeout{ cur_time });
    }
  }
  while (window.pollEvent(event)) {
    auto opt_event = snk::to_event(event);
    if (opt_event) events.push_back(*opt_event);
  }
  return events;
}

void draw_tile(snk::bounded_point_t const position,
  sf::Color const &color,
  sf::RenderWindow &window) {
  sf::RectangleShape rect{ pixel_on_draw_board({ 1, 1 }) };
  rect.setFillColor(color);
  rect.setPosition(pixel_on_draw_board(position));
  window.draw(rect);
}

void draw_snake_head(sf::RenderWindow &window, snk::running_t const &state) {
  draw_tile(state.snake().head(), sf::Color::Blue, window);
}

void draw_snake_body(sf::RenderWindow &window, snk::running_t const &state) {
  std::for_each(begin(state.snake().body_points()),
    std::prev(end(state.snake().body_points())),
    [&](auto body_point) { draw_tile(body_point, sf::Color::Green, window); });
}

void draw_snake(sf::RenderWindow &window, snk::running_t const &state) {
  draw_snake_head(window, state);
  draw_snake_body(window, state);
}

void draw_fruit(sf::RenderWindow &window, snk::running_t const &state) {
  draw_tile(state.fruit_pos(), sf::Color::Red, window);
}

void draw(sf::RenderWindow &window, snk::running_t const &state) {
  window.clear(sf::Color::Black);
  draw_fruit(window, state);
  draw_snake(window, state);
}

void draw(sf::RenderWindow &window, snk::init_t const & /*unused*/) {
  window.clear(sf::Color::Black);
  sf::Texture texture;
  sf::Sprite background;
  if (!texture.loadFromFile("data/title.png")) {
    std::cerr << "Can't load backgound\n";
  }
  background.setTexture(texture);
  window.draw(background);
}

void draw(sf::RenderWindow &window, snk::state_t const &game_state) {
  auto draw_states = nostd::overload{
    [&](snk::running_t const &state) { draw(window, state); },
    [&](snk::init_t const state) { draw(window, state); },
    [](auto const &) {},
  };
  std::visit(draw_states, game_state);
}

auto print_help() {
  std::cout << "       Snake Game\n";
  std::cout << "Start/Restart -> Enter\n";
  std::cout << "UP            -> W, K, <UP>\n";
  std::cout << "DOWN          -> S, J, <DOWN>\n";
  std::cout << "LEFT          -> A, H, <LEFT>\n";
  std::cout << "RIGHT         -> D, L, <RIGHT>\n";
  std::cout << "Play/Pause    -> Space\n";
  std::cout << "Quit          -> Escape\n";
}

void play_game(int argc, char **argv) {
  using namespace std::literals;
  auto args = std::span(argv, static_cast<std::size_t>(argc));
  if (args.size() == 2 and (args[1] == "--help"sv or args[1] == "-h"sv)) {
    print_help();
  } else {
    sf::RenderWindow window(
      sf::VideoMode(snk::game_data::win_size_x, snk::game_data::win_size_y),
      "Snake",
      sf::Style::None);
    snk::state_t state{ snk::init_t{} };
    while (window.isOpen()) {// NOLINT
      auto events = poll_events(window, state);
      for (auto event : events) {
        state = snk::handle_event(std::move(state), event);
      }
      if (rd::is<snk::closed_t>(state))
        window.close();
      else if (rd::is<snk::fruit_needed_t>(state)) {
        snk::event::fruit_generated fruit_generated_event{
          snk::random_fruit_for(std::get<snk::fruit_needed_t>(state))
        };
        state = snk::handle_event(std::move(state), fruit_generated_event);
      }
      draw(window, state);
      window.display();
      using namespace std::literals;
      std::this_thread::sleep_for(50ms);
    }
  }
}
}// namespace snk
