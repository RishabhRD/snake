#include "event_input_ops.hpp"

namespace snk {
auto to_event(sf::Event const &event) -> std::optional<event::event_t> {
  if (event.type == sf::Event::Closed) return snk::event::quit{};
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {// NOLINT
    case sf::Keyboard::H:
    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      return snk::event::direction_change::left;
    case sf::Keyboard::J:
    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      return snk::event::direction_change::down;
    case sf::Keyboard::K:
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
      return snk::event::direction_change::up;
    case sf::Keyboard::L:
    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      return snk::event::direction_change::right;
    case sf::Keyboard::Escape:
      return snk::event::quit{};
    case sf::Keyboard::Space:
      return snk::event::play_pause{};
    case sf::Keyboard::Return:
      return snk::event::start{ std::chrono::system_clock::now() };
    default:
      return std::nullopt;
    }
  } else {
    return std::nullopt;
  }
}
}// namespace snk
