#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <optional>
#include <vector>
#include "direction.hpp"
#include "event.hpp"

namespace snk::ui {
inline std::optional<events::event> transform_event(sf::Event const& evt) {
  if (evt.type == sf::Event::Closed)
    return snk::events::quit{};
  if (evt.type == sf::Event::KeyPressed) {
    switch (evt.key.code) {
      case sf::Keyboard::H:
      case sf::Keyboard::Left:
      case sf::Keyboard::A:
        return events::direction_change{direction::left};
      case sf::Keyboard::J:
      case sf::Keyboard::Down:
      case sf::Keyboard::S:
        return events::direction_change{direction::down};
      case sf::Keyboard::K:
      case sf::Keyboard::Up:
      case sf::Keyboard::W:
        return events::direction_change{direction::up};
      case sf::Keyboard::L:
      case sf::Keyboard::Right:
      case sf::Keyboard::D:
        return events::direction_change{direction::right};
      case sf::Keyboard::Escape:
        return events::quit{};
      case sf::Keyboard::Space:
        return events::play_pause{};
      case sf::Keyboard::Return:
        return events::start{};
      default:
        return std::nullopt;
    }
  } else {
    return std::nullopt;
  }
}

class sfml_window {
  sf::Window win;

 public:
  inline std::vector<events::event> poll_events() {
    std::vector<events::event> res;
    sf::Event evt{};
    while (win.pollEvent(evt)) {
      auto transformed_event = transform_event(evt);
      if (transformed_event)
        res.push_back(transformed_event.value());
    }
    return res;
  }

  inline std::size_t width() const { return win.getSize().x; }

  inline std::size_t height() const { return win.getSize().y; }
};
}  // namespace snk::ui
