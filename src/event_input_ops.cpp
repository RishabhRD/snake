#include "event_input_ops.hpp"

namespace snk {
auto to_input(sf::Event const &event) -> tl::optional<input_t> {
  if (event.type == sf::Event::Closed) return input_t::quit;
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {// NOLINT
    case sf::Keyboard::H:
    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      return input_t::left;
    case sf::Keyboard::J:
    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      return input_t::down;
    case sf::Keyboard::K:
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
      return input_t::up;
    case sf::Keyboard::L:
    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      return input_t::right;
    case sf::Keyboard::Escape:
      return input_t::quit;
    default:
      return tl::nullopt;
    }
  } else {
    return tl::nullopt;
  }
}
}// namespace snk
