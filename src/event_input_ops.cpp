#include "event_input_ops.hpp"

namespace snk {
auto to_input(sf::Event const &event) -> std::optional<input_t> {
  if (event.type == sf::Event::Closed) return snk::quit_input_t{};
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {// NOLINT
    case sf::Keyboard::H:
    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      return snk::direction_input_t::left;
    case sf::Keyboard::J:
    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      return snk::direction_input_t::down;
    case sf::Keyboard::K:
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
      return snk::direction_input_t::up;
    case sf::Keyboard::L:
    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      return snk::direction_input_t::right;
    case sf::Keyboard::Escape:
      return snk::quit_input_t{};
    case sf::Keyboard::Space:
      return snk::play_pause_input_t{};
    case sf::Keyboard::Return:
      return snk::start_input_t{};
    default:
      return std::nullopt;
    }
  } else {
    return std::nullopt;
  }
}
}// namespace snk
