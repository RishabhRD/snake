#include <functional>
#include "event_input_ops.hpp"
#include "input.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

auto handle_input(snk::input_t /*unused*/) {}

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {}

    window.clear(sf::Color::Black);

    sf::RectangleShape rectangle(sf::Vector2f(600.F, 50.F));
    window.draw(rectangle);

    window.display();
  }

  return 0;
}
